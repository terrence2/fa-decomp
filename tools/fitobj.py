#!/usr/bin/env python3
"""Adapt a CL 4.2-compiled object to its FA.EXE chunk (pilot swap step).

Usage: python3 tools/fitobj.py <cl.obj> <chunk-rva> [out.obj]

Reads the compiled object's sections/symbols, then re-emits it with:
  - .text content = CL code bytes + FA chunk tail pad (FA's compiler pads
    each function to the next 16-byte boundary with `lea esp,[esp+0]`
    (8d 64 24 00 / 8d a4 24 ..) fill; the FPO record's cbProcSize covers
    that pad, so the contribution must be the full chunk extent);
  - .debug$F = FA's own 16-byte FPO record for the chunk (offStart via
    DIR32NB reloc to the function symbol), matching the stub mechanism;
  - relocations translated: CL symbol names (e.g. @Rand@4 fastcall extern,
    or chunk anchors) are declared as undefined externals, resolved by the
    defining stub objects at link time.

Options:
  --span SIZE        the function spans SIZE bytes over CONSECUTIVE chunks
                     starting at <chunk-rva> (FA compilers emit filter/handler
                     funclets as extra "units" past the main chunk); FA bytes,
                     name, FPO record and tail then cover the whole span.
                     Offsets (patch/aliases) are span-relative.
  --alias OFF=NAME   define NAME as an additional symbol at span offset OFF
                     (needed for multi-chunk spans: FA's other chunks' fixups
                     — e.g. the scope-table funclet pointers in .rdata —
                     resolve against the inner gap anchors).
  --except-list-drop (default ON) CL emits DIR32 relocs for the three
                     fs:[__except_list] SEH sites; FA carries content 0 there
                     and NO base-reloc entries, so the linker's .reloc would
                     gain entries FA lacks. Dropped unconditionally.
"""
import json
import struct
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import coff
from peref import IMAGE_BASE
import mkstub
from padcensus import composition as pad_composition   # filler vocabulary


def read_obj(path):
    """Returns (secs, defs): secs as before; defs maps each CL-defined
    (non-section, non-.file) symbol name to (val, secnum, cls, typ) so the
    fitted object can re-define internal labels (jump-table $L targets,
    $skip_draw$...) that would otherwise resolve as undefined externals."""
    d = open(path, "rb").read()
    (mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from(
        "<HHIIIHH", d, 0)
    off = 20 + opthsz
    secs = []
    for i in range(nsec):
        name = d[off:off + 8].rstrip(b"\0").decode("latin-1")
        (vsz, va, rsz, rptr, relptr, lnptr, nrel, nln, flags) = \
            struct.unpack_from("<IIIIIIHHI", d, off + 8)
        secs.append(dict(name=name, flags=flags, content=d[rptr:rptr + rsz],
                         relptr=relptr, nrel=nrel))
        off += 40
    stro = symptr + nsym * 18

    def sym_name(p):
        if d[p:p + 4] == b"\0\0\0\0":
            o = stro + struct.unpack_from("<I", d, p + 4)[0]
            return d[o:d.index(b"\0", o)].decode("latin-1")
        return d[p:p + 8].rstrip(b"\0").decode("latin-1")

    syms, defs, n = {}, {}, 0
    while n < nsym:
        rec = symptr + n * 18
        aux = d[rec + 17]
        syms[n] = sym_name(rec)   # keyed by COFF record index (reloc refs)
        if not aux and d[rec + 16] not in (3, 103):
            # defined in a real section? (cls 6=BLOCK labels are sec-defined)
            val, secnum = struct.unpack_from("<IH", d, rec + 8)
            typ = struct.unpack_from("<H", d, rec + 14)[0]
            if secnum and secnum <= nsec:
                defs[syms[n]] = (val, secnum, d[rec + 16], typ)
        n += 1 + aux
    for s in secs:
        s["relocs"] = [(o, syms.get(sym, "#%d" % sym), t)
                       for o, sym, t in
                       (struct.unpack_from("<IIH", d, s["relptr"] + i * 10)
                        for i in range(s["nrel"]))]
    return secs, defs


def apply_patches(text, patches):
    """Rewrite CL code bytes where FA's scheduler chose differently.

    Each patch: "OFF,OLDLEN,HEX" — replace OLDLEN bytes at OFF with HEX
    (OLDLEN 0 = insert; empty HEX = delete). Reloc sites inside a removed /
    replaced span are dropped; sites after the span shift by the length
    delta of every earlier patch. Optional ",SITE:TYPE:SYMBOL" fields attach
    new relocs at SITE (post-patch span offset) — TYPE 6 = DIR32, 20 = REL32;
    SYMBOL is a CL-level name resolved later by --map remapping.
    """
    txt = text["content"]
    for spec in patches:
        parts = spec.split(",")
        off, oldlen = int(parts[0], 0), int(parts[1], 0)
        new = bytes.fromhex(parts[2]) if parts[2] else b""
        newsites = [(int(p.split(":")[0], 0), int(p.split(":")[1], 0),
                     p.split(":", 2)[2]) for p in parts[3:] if p]
        rels = [(r[0] + len(new) - oldlen, r[1], r[2])
                if r[0] >= off + oldlen else r
                for r in text["relocs"]
                if not (off <= r[0] < off + oldlen)]
        text["relocs"] = rels
        txt[off:off + oldlen] = new
        for site, t, sym in newsites:
            o2 = off + site
            if "+" in sym:
                # interior newsite "SYM+0xN": sym must be linked bare —
                # the delta rides in the payload, not the symbol (DIR32
                # final = symVA + content). Bare tokens keep the hex bytes
                # untouched: the standing convention is hex = delta.
                base_, delta_ = sym.rsplit("+", 1)
                struct.pack_into("<I", txt, o2, int(delta_, 0))
                sym = base_
                print("newsite @%#x: %s t%d (payload := 0x%x)"
                      % (o2, base_, t, int(delta_, 0)))
            text["relocs"].append((o2, sym, t))
        print("patch @%#x: %d -> %d bytes (%s)" %
              (off, oldlen, len(new), new.hex() or "-"))


def main():
    cl_obj, rva = sys.argv[1], int(sys.argv[2], 0)
    out, remap, tailaccept, patches = None, {}, False, []
    aliases, span_size = [], None
    argv = sys.argv[3:]
    i = 0
    while i < len(argv):
        if argv[i] == "--map":
            f, t = argv[i + 1].split("=", 1)
            remap[f] = t
            i += 2
        elif argv[i] == "--tail-accept":
            tailaccept = True
            i += 1
        elif argv[i] == "--patch":
            patches.append(argv[i + 1])
            i += 2
        elif argv[i] == "--span":
            span_size = int(argv[i + 1], 0)
            i += 2
        elif argv[i] == "--alias":
            ao, an = argv[i + 1].split("=", 1)
            aliases.append((int(ao, 0), an))
            i += 2
        else:
            out = argv[i]; i += 1
    if out is None:
        out = cl_obj.rsplit(".", 1)[0] + "_fit.obj"
    # "TO+0xdelta" (or plain decimal) adds an addend into the reloc site's
    # content dword — used when the target is INSIDE a gap chunk whose stub
    # symbol only covers the chunk start
    addend = {k: 0 for k in remap}
    for k, v in list(remap.items()):
        # "TO+0xdelta"/"TO-0xdelta" (or plain decimal): a (possibly negative)
        # addend baked into the reloc site's content dword — used when the
        # target is INSIDE a gap chunk / shared symbol whose stub symbol only
        # covers the chunk start
        import re as _re
        m = _re.match(r"^(.+)([+-]0x[0-9a-fA-F]+|[+-]\d+)$", v)
        if m:
            remap[k] = m.group(1)
            addend[k] = int(m.group(2), 16) if "x" in m.group(2) \
                else int(m.group(2))
    secs, defs = read_obj(cl_obj)
    text_idx = secs.index(next(s for s in secs if s["name"] == ".text")) + 1
    text = next(s for s in secs if s["name"] == ".text")
    text["content"] = bytearray(text["content"])
    if patches:
        apply_patches(text, patches)
    L = json.load(open("build/layout.json"))
    exe = open("FA/FA.EXE", "rb").read()
    if span_size is not None:
        cs = [c for c in L["text_chunks"]
              if rva <= c["rva"] < rva + span_size]
        assert cs[0]["rva"] == rva, "span must start on a chunk boundary"
        assert sum(c["size"] for c in cs) == span_size, \
            "span chunks do not tile [rva, rva+%#x)" % span_size
    else:
        cs = [next(c for c in L["text_chunks"] if c["rva"] == rva)]
    fa_bytes = b"".join(exe[c["off"]:c["off"] + c["size"]] for c in cs)
    fpo = bytes.fromhex(cs[0]["fpo_rec"]) if cs[0].get("fpo_rec") else None
    tail = fa_bytes[len(text["content"]):]
    # Residue beyond CL code must be FA filler explained by the census table
    # (tools/padcensus.py VOCAB — full deco of FA/CL-observed pad bytes).
    # Proven pad compositions copy without a flag; anything else needs
    # --tail-accept (and a provenance entry in swap.json).
    comp = pad_composition(tail) if tail else ()
    if tail and comp is None and not tailaccept:
        sys.exit("FATAL: unexplained tail bytes %s beyond CL code for %#x "
                 "(not a census filler composition)" % (tail.hex(), rva))
    if tail and comp is not None:
        print("NOTE: tail = census-proven filler %s (%d B) for %#x"
              % ("+".join(comp), len(tail), rva))
    elif tail:
        print("NOTE: tail-accept: copying %d unexplained FA tail byte(s) %s "
              "for %#x (code+tables matched; residue is FA's own)"
              % (len(tail), tail.hex(), rva))
    name = cs[0]["name"] or "$FA$_span_%06x" % rva
    dropped = n_list = 0
    relocs = []
    for o, n_, t in text["relocs"]:
        if n_ == "__except_list":
            dropped += 1                                 # fs-relative: FA's
            continue                                     # image has no fixup
        v = remap.get(n_, n_)
        d_ = addend.get(n_, 0)
        if d_:
            # bake the extra addend into the referenced content dword
            site = struct.unpack_from("<i", text["content"], o)[0]
            struct.pack_into("<i", text["content"], o, site + d_)
        elif "+" in v:
            # newsite "SITE:TYPE:SYM+0xNNN": SYM is only linkable bare —
            # strip the interior offset and carry it in the content dword
            # (DIR32 final = symVA + content; REL32 final = symVA + content
            # − (site+4)). The payload here is either FA's baked absolute
            # dword (from a transplant) or zero — both replaced by DELTA.
            base_, delta_ = v.rsplit("+", 1)
            struct.pack_into("<i", text["content"], o, int(delta_, 0))
            print("NOTE: newsite sym %#x %s: delta +0x%x baked into payload "
                  "(sym bare %s)" % (o, v, int(delta_, 0), base_))
            v = base_
        relocs.append((o, v, t))
    # Byte-verify (wave-2 lesson): outside the reloc'd dword sites the
    # patched CL code must equal FA's chunk bytes exactly — the content
    # dwords a link fixes up are remap/label values (exempt), everything
    # else is compiler output. Without this, a semantically reordered
    # object with the right size/reloc sites fits silently and only fails
    # at Gate 1.
    mask = bytearray(len(text["content"]))
    for o, _, _ in relocs:
        mask[o:o + 4] = b"\x01" * 4
    # The obj contributes len(content) bytes at the chunk VA (the stub it
    # replaces covered exactly the chunk extent): code LONGER than the chunk
    # shifts every downstream .text obj one byte per extra byte, and the
    # verify loop below only sees min(len, FA) — so an over-long patched
    # code must fail here (wave-32: stale patches appended 2 junk bytes past
    # __dosmaperr's 115-B chunk; the +2 shift cascaded 52360 B at gate).
    if len(text["content"]) > len(fa_bytes):
        sys.exit("FATAL: patched CL code %#x B > FA chunk %#x B for %#x — "
                 "the obj would shift .text downstream; fix/trim the "
                 "patches" % (len(text["content"]), len(fa_bytes), rva))
    diffs = [i for i in range(min(len(text["content"]), len(fa_bytes)))
             if text["content"][i] != fa_bytes[i] and not mask[i]]
    if diffs:
        runs = []
        for i in diffs:
            if runs and i == runs[-1][1]:
                runs[-1][1] = i + 1
            else:
                runs.append([i, i + 1])
        sys.exit("FATAL: CL code != FA bytes at %d non-reloc byte(s) for "
                 "%#x: %s%s" % (len(diffs), rva, ", ".join(
                     "%#x-%#x" % (a, b - 1) for a, b in runs[:6]),
                 "  (add a census-proven tail or --patch if this is an FA "
                 "codegen delta)" if len(diffs) > 4 else "  (fix the source)"))
    extra = [(an, ao, 1, coff.SYM_EXTERNAL, coff.TYPE_FUNCTION, b"")
             for ao, an in aliases]
    # re-define CL's internally-referenced labels against the fitted .text
    # (sec 1) so the linker finds them — same val/cls/typ as the CL obj
    for o, n_, t in relocs:
        if n_ not in remap and n_ in defs and n_ != name \
                and defs[n_][1] == text_idx \
                and all(e[0] != n_ for e in extra):
            val, _, cls, typ = defs[n_]
            extra.append((n_, val, 1, cls, typ, b""))
    if extra:
        print("defines: %s" % ", ".join(
            "%s@%#x" % (e[0], e[1]) for e in extra))
    print("chunk %s @ %#x: cl code 0x%x + pad 0x%x = 0x%x; %d relocs%s"
          % (name, rva, len(text["content"]), len(tail), len(fa_bytes),
             len(relocs),
             "; dropped %d __except_list" % dropped if dropped else ""))
    if span_size is not None:
        print("span units: %s" % ", ".join(
            "%#x:%#x" % (c["rva"], c["size"]) for c in cs[1:]))
    # plain align-1 flags, like the stub .text the object replaces: the CL
    # COMDAT flag keys the section on the generic ".text" symbol, and link
    # 4.20 dedups all same-keyed COMDAT sections, dropping every fitted obj
    # after the first (found with the 7-obj link; see build/mt7).
    #
    # Span: one .debug$F part per chunk with an FA record (the stub singleton
    # being replaced contributed those records to FA's FPO payload; the fit
    # obj must re-emit them or the payload/debug-dir shifts by 16 B/record).
    dbg_parts = []
    if span_size is not None:
        fpo_set = set(mkstub.fa_fpo_records())
        for c in cs:
            if (c["rva"], c["size"]) not in fpo_set:
                continue
            r = (bytes.fromhex(c["fpo_rec"]) if c.get("fpo_rec") else
                 struct.pack("<IIIHBB2x", c["rva"], c["size"], 0, 0, 0, 0))
            an = c["name"] or "$FA$_t_%06x" % (c["rva"] + IMAGE_BASE)
            dbg_parts.append((".debug$F", coff.S_DEBUGF_PLAIN,
                              b"\0\0\0\0" + r[4:], [(0, an, coff.RELOC_DIR32NB)]))
        obj = coff.build_stub_obj(text["content"] + tail, 0x00100020, name,
                                  fpo_rec=None, debugf_assoc=False,
                                  more_sections=dbg_parts,
                                  main_relocs=relocs, more_syms=extra)
    else:
        obj = coff.build_stub_obj(
            text["content"] + tail, 0x00100020, name, fpo_rec=fpo,
            debugf_assoc=False, main_relocs=relocs, more_syms=extra)
    open(out, "wb").write(obj)
    print("wrote", out)


if __name__ == "__main__":
    main()