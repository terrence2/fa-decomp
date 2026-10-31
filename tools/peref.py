#!/usr/bin/env python3
"""Derive the canonical FA.EXE layout: ordered symbols with extents, FPO
records, imports/exports/resources metadata — the input for stub generation.

Outputs build/layout.json.
"""
import json
import struct
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
from parsesms import parse_sms

IMAGE_BASE = 0x400000


class PE:
    def __init__(self, path):
        self.data = data = open(path, "rb").read()
        e = struct.unpack_from("<I", data, 0x3C)[0]
        self.pe_off = e
        (self.machine, self.nsec, self.ts, self.symptr, self.nsym,
         self.opthdrsize, self.chars) = struct.unpack_from("<HHIIIHH", data, e + 4)
        self.opt = e + 4 + 20
        (self.imagebase, self.secalign, self.filealign) = struct.unpack_from("<III", data, self.opt + 28)
        self.subsystem, = struct.unpack_from("<H", data, self.opt + 68)
        self.secs = []
        sp = self.opt + self.opthdrsize
        for i in range(self.nsec):
            name = data[sp:sp + 8].rstrip(b"\0").decode()
            (vsz, va, rsz, rptr) = struct.unpack_from("<IIII", data, sp + 8)
            (sflags,) = struct.unpack_from("<I", data, sp + 36)
            self.secs.append(dict(name=name, va=va, vsz=vsz, rawptr=rptr, rawsz=rsz, flags=sflags))
            sp += 40

    def sec_by_rva(self, rva):
        for s in self.sections:
            if s['va'] <= rva < s['va'] + max(s['vsz'], s['rawsz']):
                return s
        return None

    sections = property(lambda self: self.secs)

    def rva_to_off(self, rva):
        for s in self.secs:
            if s["va"] <= rva < s["va"] + max(s["vsz"], s["rawsz"]):
                return s["rawptr"] + (rva - s["va"])
        return None

    def read_va(self, va, n):
        o = self.rva_to_off(va - IMAGE_BASE)
        if o is None:
            return None
        return self.data[o:o + n]


def parse_fpo(pe):
    """Return (recs, None) where recs[offStart_rva] = {rva/size/locals/locals/rec}.
    The exe-level FPO payload is a straight concatenation of 16-byte FPO_DATA
    records starting at offset 0 (verified: blob[0:16] is a valid record
    (offStart .text rva 0x1000) — there is no separate header)."""
    fpo = next(e for e in parse_debug(pe) if e["typ"] == 3)
    blob = pe.data[fpo["ptr"]:fpo["ptr"] + fpo["size"]]
    out = {}
    for o in range(0, len(blob), 16):
        ol = struct.unpack_from("<I", blob, o)[0]
        out[ol] = dict(rva=ol, size=struct.unpack_from("<I", blob, o + 4)[0],
                       locals=struct.unpack_from("<I", blob, o + 8)[0],
                       rec=blob[o:o + 16])
    return out, None


def debug_dir_off(pe):
    """File offset of the CodeView debug directory (it lives inside .rdata,
    RVA pointed to by data-directory entry 6, not at opt+96)."""
    rva, sz = struct.unpack_from("<II", pe.data, pe.opt + 96 + 6 * 8)
    if not rva:
        return None, 0
    return pe.rva_to_off(rva), sz


def parse_debug(pe):
    doff, dsize = debug_dir_off(pe)
    out = []
    for i in range(dsize // 28):
        c, t, mj, mn, typ, size, rva, ptr = struct.unpack_from("<IIHHIIII", pe.data, doff + i * 28)
        if rva or ptr:
            out.append(dict(typ=typ, size=size, rva=rva, ptr=ptr, ts=t))
    return out


def parse_exports(pe, rva=None):
    if rva is None:
        (rva, _) = struct.unpack_from("<II", pe.data, pe.opt + 96 + 0 * 8)
    off = pe.rva_to_off(rva)
    (flags, ts, maj, minr, nameRva, base, nn, nnp, aaddr, anames, nords_rva) = struct.unpack_from(
        "<IIHHIIIIIII", pe.data, off)
    funcs = [struct.unpack_from("<I", pe.data, pe.rva_to_off(aaddr) + i * 4)[0] for i in range(nn)]
    names = []
    if anames and nnp:
        noff = pe.rva_to_off(anames)
        nords = pe.rva_to_off(nords_rva)
        for i in range(nnp):
            rva = struct.unpack_from("<I", pe.data, noff + i * 4)[0]
            o = pe.rva_to_off(rva)
            end = pe.data.index(b"\0", o)
            names.append((pe.data[o:end].decode(), struct.unpack_from("<H", pe.data, nords + i * 2)[0] + base))
    return dict(name=pe.data[pe.rva_to_off(nameRva):pe.data.index(b"\0", pe.rva_to_off(nameRva))].decode(),
                ord_base=base, rva=funcs, names=names)


def parse_imports(pe):
    (rva, _) = struct.unpack_from("<II", pe.data, pe.opt + 96 + 1 * 8)
    off = pe.rva_to_off(rva)
    out = []
    while True:
        oft, tds, fwd, nameRva, ft = struct.unpack_from("<IIIII", pe.data, off)
        if nameRva == 0:
            break
        o = pe.rva_to_off(nameRva)
        end = pe.data.index(b"\0", o)
        dll = pe.data[o:end].decode()
        t2 = pe.rva_to_off(oft if oft else ft)
        thunks = []
        while True:
            v, = struct.unpack_from("<I", pe.data, t2)
            if v == 0:
                break
            if v & 0x80000000:
                thunks.append(("#ord%d" % (v & 0xffff), "ord", v & 0xffff))
            else:
                o2 = pe.rva_to_off(v + 2)
                end2 = pe.data.index(b"\0", o2)
                nm = pe.data[o2:end2].decode()
                thunks.append((nm, "name", None))
            t2 += 4
        out.append(dict(dll=dll, thunks=thunks))
        off += 20
    return out


def chunk_text(fpo_recs, lo, hi, name_at):
    """Tile [lo,hi) into chunks: one chunk per FPO extent, residual gaps split
    at SMS symbol starts (a boundary == an existing end is skipped). Adjacent
    FPO spans stay separate chunks so SMS names land at chunk starts; true
    overlaps are merged and counted."""
    spans = sorted(fpo_recs)
    chunks, overlaps = [], 0
    prev_end = None
    for rva in spans:
        rec = fpo_recs[rva]
        a, b = rva, rva + rec["size"]
        if prev_end is not None and a < prev_end:
            overlaps += 1
            # true overlap: extend the previous chunk to cover it
            chunks[-1]["size"] = max(prev_end, b) - chunks[-1]["rva"]
            prev_end = chunks[-1]["rva"] + chunks[-1]["size"]
            if b > prev_end:
                chunks.append(dict(rva=b, size=0, fpo=True))
                prev_end = b
            continue
        chunks.append(dict(rva=a, size=b - a, fpo=True))
        prev_end = b
        gap_end = next((s for s in spans if s > rva), hi)
        if b < gap_end:
            chunks += _gap_chunks(name_at, b, gap_end)
    if not chunks:
        chunks += _gap_chunks(name_at, lo, hi) if hi > lo else []
    elif lo < chunks[0]["rva"]:
        chunks = _gap_chunks(name_at, lo, chunks[0]["rva"]) + chunks
    return chunks, overlaps


def _gap_chunks(name_at, a, b):
    """Split [a,b) at each SMS symbol start strictly inside it."""
    starts = sorted(v for v in name_at if a < v < b)
    pts = [a] + starts
    out = []
    for j, p in enumerate(pts):
        nxt = pts[j + 1] if j + 1 < len(pts) else b
        if p != nxt:
            out.append(dict(rva=p, size=nxt - p, fpo=False))
    return out


def _inside(rva, chunks):
    return any(c["rva"] < rva < c["rva"] + c["size"] for c in chunks)


def main():
    pe = PE("FA/FA.EXE")
    fpo_recs, _hdr = parse_fpo(pe)
    dbg = parse_debug(pe)
    exp = parse_exports(pe)
    imps = parse_imports(pe)
    sms = parse_sms("FA/FA.SMS")

    secs = {s["name"]: s for s in pe.secs}
    text, rdata, data = secs[".text"], secs[".rdata"], secs[".data"]
    # section "va" fields are RVAs; normalize to ABSOLUTE VA space for
    # comparisons (leave pe.secs untouched so rva_to_off keeps working)
    for s in (text, rdata, data, ):
        s = dict(s)
    text = dict(text, va=text["va"] + IMAGE_BASE)
    rdata = dict(rdata, va=rdata["va"] + IMAGE_BASE)
    data = dict(data, va=data["va"] + IMAGE_BASE)
    name_at = {va: nm for va, nm in sms}

    # --- .text chunks (absolute VA space) ---
    text_names = {va: nm for va, nm in sms
                  if text["va"] <= va < text["va"] + text["vsz"]}
    fpo_abs = {IMAGE_BASE + rva: rec for rva, rec in fpo_recs.items()}
    tchunks, overlaps = chunk_text(fpo_abs, text["va"], text["va"] + text["vsz"],
                                   text_names)

    text_chunks = []
    for c in tchunks:
        rec = fpo_abs.get(c["rva"])
        text_chunks.append(dict(
            va=c["rva"], rva=c["rva"] - IMAGE_BASE, size=c["size"], fpo=c["fpo"],
            name=text_names.get(c["rva"]),
            fpo_locals=rec["locals"] if rec else None,
            fpo_rec=rec["rec"].hex() if rec else None,
            off=pe.rva_to_off(c["rva"] - IMAGE_BASE)))
    chunk_starts = {c["rva"] for c in tchunks}
    swallowed = sorted(nm for va, nm in text_names.items()
                       if va not in chunk_starts and _inside(va, tchunks))

    # --- .data chunks: every section byte belongs to one chunk ---
    data_names = sorted(va for va, nm in sms
                        if data["va"] <= va < data["va"] + data["vsz"])
    data_hi = max(data["vsz"], data["rawsz"]) + data["va"]
    data_chunks = []
    starts = ([data["va"]] if data["va"] not in data_names else []) + data_names
    for i, va in enumerate(starts):
        nxt = starts[i + 1] if i + 1 < len(starts) else data_hi
        data_chunks.append(dict(
            va=va, rva=va - IMAGE_BASE, size_full=nxt - va,
            size_file=max(0, min(nxt, data["va"] + data["rawsz"]) - va),
            name=name_at.get(va), off=pe.rva_to_off(va - IMAGE_BASE)))
    dcovered = sum(c["size_full"] for c in data_chunks)

    # --- .rdata symbols (metadata only — linker-generated, never stubbed) ---
    rdata_syms = [dict(va=va, name=nm) for va, nm in sms
                  if rdata["va"] <= va < rdata["va"] + max(rdata["vsz"], rdata["rawsz"])]

    out = dict(
        image_base=IMAGE_BASE,
        timestamp=pe.ts,
        secs=pe.secs,
        debug=dbg,
        exports=exp,
        imports=imps,
        text=dict(va=text["va"], vsz=text["vsz"],
                  rawptr=text["rawptr"], rawsz=text["rawsz"]),
        rdata=dict(va=rdata["va"], vsz=rdata["vsz"],
                   rawptr=rdata["rawptr"], rawsz=rdata["rawsz"]),
        data=dict(va=data["va"], vsz=data["vsz"],
                  rawptr=data["rawptr"], rawsz=data["rawsz"]),
        text_chunks=text_chunks,
        data_chunks=data_chunks,
        rdata_syms=rdata_syms,
        fpo_bytes=_hdr.hex() if _hdr else "",
        fpo_count=len(fpo_recs),
        fpo_overlaps=overlaps,
        swallowed_names=swallowed,
        syms=sms,
    )
    import os
    os.makedirs("build", exist_ok=True)
    with open("build/layout.json", "w") as f:
        json.dump(out, f, indent=1)

    fposize = sum(r["size"] for r in fpo_recs.values())
    covered = sum(c["size"] for c in tchunks)
    nfpo = sum(1 for c in text_chunks if c["fpo"])
    nnamed = sum(1 for c in text_chunks if c["name"])
    print("FPO: %d recs, fn code 0x%x, %d overlap(s)" % (len(fpo_recs), fposize, overlaps))
    print(".text: %d chunks tile 0x%x (chunks cover 0x%x): %d fpo, %d gap, %d named;"
          " %d named-inside swallowed"
          % (len(text_chunks), text["vsz"], covered, nfpo, len(text_chunks) - nfpo,
             nnamed, len(swallowed)))
    print(".data: %d chunks cover 0x%x of 0x%x (head gap %s), %d named"
          % (len(data_chunks), dcovered, data_hi - data["va"],
             "none" if not data_chunks or data_chunks[0]["name"] is None and
             data_chunks[0]["size_full"] > 0 and data_chunks[0]["rva"] == data["va"] else 0,
             sum(1 for c in data_chunks if c["name"])))
    print("rdata syms: %d; sms total: %d" % (len(rdata_syms), len(sms)))
    for c in text_chunks[:3] + text_chunks[-3:]:
        print("  text 0x%06x %-32s size=0x%-5x fpo=%s"
              % (c["va"], (c["name"] or "<gap>")[:32], c["size"], c["fpo"]))
    for c in (data_chunks[:2] + data_chunks[-2:]):
        print("  data 0x%06x %-32s size_file=0x%-5x name=%s"
              % (c["va"], (c["name"] or "<gap>")[:32], c["size_file"], c["name"] is not None))


if __name__ == "__main__":
    main()