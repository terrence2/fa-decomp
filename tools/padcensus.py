#!/usr/bin/env python3
"""Filler/pad census for FA.EXE and CL objects (patch-site forensics).

Modes:
  fa    census of FA/FA.EXE .text: every FPO-record function extent and the
        bytes between consecutive records (pads) and inside record tails;
        tabulates filler compositions.
  scan  raw occurrences of candidate filler sequences with context.
  objs  dump the .text-section tails of CL-compiled objects (battery) —
        with /Gy each function is its own COMDAT .text, so the tail is the
        compiler's alignment filler for (codesize mod 16).

Usage:
  python3 tools/padcensus.py fa
  python3 tools/padcensus.py scan 05pad|8bff
  python3 tools/padcensus.py objs build/probe/pads/*.obj
"""
import struct
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import coff
from mkstub import fa_fpo_records

# filler vocabulary: known no-op multi-byte sequences (x86).  Extend this
# table as unknown compositions surface in the census output.
VOCAB = (
    b"\x90",                    # nop
    b"\x66\x90",                # xchg ax,ax (2-B nop)
    b"\x8b\xff",                # mov edi,edi (2-B)
    b"\x8b\xc0",                # mov eax,eax (2-B)
    b"\x8b\xc9",                # mov ecx,ecx
    b"\x8b\xf9",                # mov edi,ecx
    b"\x87\xff",                # xchg edi,edi
    b"\x9b",                    # wait (seen in fitobj's allowed set)
    b"\x8d\x64\x24\x00",        # lea esp,[esp+0] (4-B)
    b"\x8d\x6c\x24\x00",        # lea ebp,[esp+0]
    b"\x8d\x49\x00",            # lea ecx,[ecx+0]
    b"\x8d\x40\x00",            # lea eax,[eax+0]
    b"\x8d\x9b\x00\x00\x00\x00",  # lea ebx,[ebx+0] (6-B; 334 sites in FA)
    b"\x8d\xa4\x24\x00\x00\x00\x00",  # lea esp,[esp+0] (7-B)
    b"\x8d\xac\x24\x00\x00\x00\x00",
    b"\x05\x00\x00\x00\x00",    # add eax,0 (the mystery 5-B sequence)
)

FA = "FA/FA.EXE"
FPO_OFF, FPO_END = 0x131B10, 0x13D5B0
TEXT_RVA0, TEXT_RVA1 = 0x1000, 0xE5000   # image .text extent
DELTA = 0xC00                            # file_off = rva - DELTA (0x1000 - 0x400)


def composition(bs):
    """Decode a byte span into a vocab token list; None if not fully filler."""
    toks, i = [], 0
    while i < len(bs):
        for v in sorted(VOCAB, key=len, reverse=True):
            if bs[i:i + len(v)] == v:
                toks.append(v.hex())
                i += len(v)
                break
        else:
            return None
    return tuple(toks)


def hist_add(hist, comp, ctx):
    hist.setdefault(comp, []).append(ctx)


def fa_census():
    exe = open(FA, "rb").read()
    recs = sorted(fa_fpo_records())
    between, inside = {}, {}
    unknown_between, unknown_inside = [], []

    # pads BETWEEN record end and next record start (and after the last rec
    # up to .text end)
    for i, (rva, sz) in enumerate(recs):
        end = rva + sz
        nxt = recs[i + 1][0] if i + 1 < len(recs) else TEXT_RVA1
        if nxt <= end:
            continue
        bs = exe[end - DELTA:nxt - DELTA]
        comp = composition(bs)
        gap_to_16 = (16 - end % 16) % 16
        if comp is None:
            unknown_between.append((end, bs, gap_to_16))
        else:
            hist_add(between, comp, (end, gap_to_16))

    # "inside record" = the trailing filler-looking run at a record END that
    # is already 16-aligned (candidate content+pad-in-cbProcSize records)
    for rva, sz in recs:
        end = rva + sz
        if end % 16:
            continue
        # try suffix lengths 15..1, longest full-vocab suffix
        found = None
        for L in range(min(15, sz), 0, -1):
            comp = composition(exe[end - L - DELTA:end - DELTA])
            if comp is not None:
                found = (L, comp)
                break
        if found is not None:
            hist_add(inside, found[1], (end, found[0]))
        else:
            unknown_inside.append(end)

    return recs, between, unknown_between, inside, unknown_inside


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "fa"

    if mode == "objs":
        for p in sys.argv[2:]:
            d = open(p, "rb").read()
            (mach, nsec, ts, symptr, nsym, opthsz, chars) = \
                struct.unpack_from("<HHIIIHH", d, 0)
            off = 20 + opthsz
            for i in range(nsec):
                nm = d[off:off + 8].rstrip(b"\0").decode("latin-1")
                (vsz, va, rsz, rptr, relptr, lnptr, nrel, nln, flg) = \
                    struct.unpack_from("<IIIIIIHHI", d, off + 8)
                off += 40
                if nm != ".text" or rsz == 0:
                    continue
                content = d[rptr:rptr + rsz]
                gap = 16 - rsz % 16 if rsz % 16 else 0
                tail = content[-gap:] if gap else b""
                comp = composition(tail)
                print("  %s sec%d codesz=0x%-4x gap=%-2d flags=%#08x "
                      "tail=%s comp=%s"
                      % (p.split("/")[-1], i + 1, rsz, gap,
                         flg, tail.hex() or "-",
                         "+".join(comp) if comp else "UNKNOWN"))
        return

    if mode == "scan":
        exe = open(FA, "rb").read()
        pat = bytes.fromhex(sys.argv[2])
        recs = sorted(fa_fpo_records())
        i, n = 0, 0
        # .text file extent: 0xe5000-0xc00 = 0xe4400
        file_end = 0xE4400   # .text file extent
        while True:
            j = exe.find(pat, i, file_end)
            if j < 0:
                break
            rva = j + DELTA
            owner = next(((r, s) for r, s in recs if r <= rva < r + s), None)
            nxts = [r for r, s in recs if r > rva]
            nxt = min(nxts) if nxts else TEXT_RVA1
            print("  rva=%#08x off=%#08x ends16=%s rec=%s "
                  "in-between=%s nxt_rec=0x%x ctx=%s"
                  % (rva, j, (rva + len(pat)) % 16 == 0,
                     "0x%x+0x%x" % owner if owner else "-",
                     "N" if owner else "Y", nxt,
                     exe[j:j + 16].hex()))
            n += 1
            i = j + 1
        print("== %d occurrence(s) of %s in .text" % (n, pat.hex()))
        return

    recs, between, unb, inside, uni = fa_census()
    print("== FA census: %d FPO records" % len(recs))
    print("-- between-record regions (pads outside cbProcSize):")
    tot = sum(len(v) for v in between.values())
    print("-- inside-record tail runs at 16-aligned record ends:")
    tot += sum(len(v) for v in inside.values())
    for h, label in ((between, "between"), (inside, "inside")):
        print("-- %s compositions (n=%d distinct):"
              % (label, sum(len(v) for v in h.values())))
        for comp in sorted(h, key=lambda c: -len(h[c])):
            ex = h[comp][0]
            print("   %-40s x%-4d e.g. end=%#x gap-to-16=%#x"
                  % ("+".join(comp), len(h[comp]), ex[0], ex[1]))
    if unb:
        print("-- UNKNOWN between regions: %d" % len(unb))
        for end, bs, g in unb[:20]:
            print("   end=%#x gap16=%d bytes=%s" % (end, g, bs.hex()))
    if uni:
        print("-- 16-aligned record ends with NO filler tail: %d (e.g. %s)"
              % (len(uni), ", ".join("%#x" % e for e in uni[:8])))
    print("== observed pad regions total: %d" %
          (tot))


if __name__ == "__main__":
    main()