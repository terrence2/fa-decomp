#!/usr/bin/env python3
"""Import-ref obj variants, probing link 4.20's import synthesis:
  realref  -- real .rdata section, DIR32 relocs to __imp__ symbols
  nbref    -- same but DIR32NB relocs
Which one yields complete .idata (INT/IAT + hint/name entries)?"""
import struct
import sys

sys.path.insert(0, "tools")
import coff


def ref_obj(content, relocs, secname=".rdata", flags=0x40300040):
    st = coff.SymTable()
    secs = [(secname, flags, content, relocs)]
    externals = sorted({r[1] for r in relocs})
    names = ["__imp__GetTickCount@0", "__imp__timeGetTime@0"]
    aux = coff._aux_bytes(flags, content, len(relocs), 0, 0)
    st.add(secname, 0, 1, coff.SYM_SECTION, aux=aux)
    st.add("_ref", 0, 1, coff.SYM_EXTERNAL, typ=0)
    for nm in names:
        if any(relocs[i][1] == i for i in range(len(relocs))) or True:
            pass
    # sym indices: relocs reference via placeholder below
    idx = {}
    for nm in names:
        idx[nm] = st.add(nm, 0, 0, coff.SYM_EXTERNAL)
    nrel = len(st.recs)
    rel = b"".join(struct.pack("<IIH", rva, idx[names[sym]], typ)
                   for rva, sym, typ in relocs)
    nsym = len(st.recs)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0, nsym, 0, 0))
    rawoff = 20 + 40
    relofs = rawoff + len(content)
    secblk = secname.encode().ljust(8, b"\0") + struct.pack(
        "<IIIIIIHHI", 0, 0, len(content), rawoff, relofs, 0, len(relocs), 0, flags)
    symoff = relofs + len(rel)
    struct.pack_into("<I", hdr, 8, symoff)
    return bytes(hdr) + secblk + content + rel + st.bytes()


if __name__ == "__main__":
    c2 = bytes(4 * 2)
    open("build/m0/ref_real.obj", "wb").write(
        ref_obj(c2, ((0, 0, coff.RELOC_DIR32), (4, 1, coff.RELOC_DIR32))))
    open("build/m0/ref_nb.obj", "wb").write(
        ref_obj(c2, ((0, 0, coff.RELOC_DIR32NB), (4, 1, coff.RELOC_DIR32NB))))
    print("built ref_real.obj ref_nb.obj")