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
"""
import json
import struct
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import coff
from peref import IMAGE_BASE


def read_obj(path):
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

    syms, n = {}, 0
    while n < nsym:
        rec = symptr + n * 18
        aux = d[rec + 17]
        syms[n] = sym_name(rec)   # keyed by COFF record index (reloc refs)
        n += 1 + aux
    for s in secs:
        s["relocs"] = [(o, syms.get(sym, "#%d" % sym), t)
                       for o, sym, t in
                       (struct.unpack_from("<IIH", d, s["relptr"] + i * 10)
                        for i in range(s["nrel"]))]
    return secs


def main():
    cl_obj, rva = sys.argv[1], int(sys.argv[2], 0)
    out = sys.argv[3] if len(sys.argv) > 3 else cl_obj.rsplit(".", 1)[0] + "_fit.obj"
    secs = read_obj(cl_obj)
    text = next(s for s in secs if s["name"] == ".text")
    L = json.load(open("build/layout.json"))
    chunk = next(c for c in L["text_chunks"] if c["rva"] == rva)
    exe = open("FA/FA.EXE", "rb").read()
    fa_bytes = exe[chunk["off"]:chunk["off"] + chunk["size"]]
    fpo = bytes.fromhex(chunk["fpo_rec"]) if chunk.get("fpo_rec") else None
    tail = fa_bytes[len(text["content"]):]
    if not (set(tail) <= {0x8d, 0x64, 0x24, 0xa4, 0x00}):
        sys.exit("FATAL: unexplained tail bytes %s beyond CL code for %#x"
                 % (tail.hex(), rva))
    name = chunk["name"] or "$FA$chunk_%06x" % rva
    relocs = [(o, n_, t) for o, n_, t in text["relocs"]]
    print("chunk %s @ %#x: cl code 0x%x + pad 0x%x = 0x%x; %d relocs"
          % (name, rva, len(text["content"]), len(tail), chunk["size"],
             len(relocs)))
    obj = coff.build_stub_obj(
        text["content"] + tail,
        text["flags"], name, fpo_rec=fpo, debugf_assoc=False,
        main_relocs=relocs)
    open(out, "wb").write(obj)
    print("wrote", out)


if __name__ == "__main__":
    main()