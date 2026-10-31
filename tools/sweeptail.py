#!/usr/bin/env python3
"""Synthetic .reloc-tail probes: build objs with controlled fixup layouts,
link them together, and report the image .reloc vsz/content-end/tail.

Sweeps: fixups per page, pages touched, chunk alignment boundaries.
Artifacts: build/m0/tw/ (N objects + one rsp per case)."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import coff
from coff import SymTable, SYM_SECTION, SYM_EXTERNAL, RELOC_DIR32, _aux_bytes

OUT = "build/m0/tw"
PAGESZ = 0x1000


def obj_text_fixups(path, pages_fixups, pad_last=0, npad=1):
    """One obj: .text = len(pages_fixups) pages; page p carries fixups at the
    given page offsets, each DIR32 -> _ANCHOR (in a trailing .data section).
    pad_last: extra fixup-padding pages after the fixup pages. Each additional
    obj is a separate module (npad objs, only the first has content)."""
    content = bytes(PAGESZ * len(pages_fixups))
    relocs = []
    for pg, fx in pages_fixups:
        for o in fx:
            relocs.append((pg * PAGESZ + o, "_ANCHOR", RELOC_DIR32))
    st = SymTable()
    st.add(".text", 0, 1, SYM_SECTION, aux=_aux_bytes(0x00100020, content,
                                                      len(relocs), 1, 0))
    ia = st.add("_ANCHOR", 0, 0, 2)   # undefined external
    symidx = {"_ANCHOR": ia}
    nsym = len(st.recs)
    rel = b"".join(struct.pack("<IIH", o, symidx[n], t)
                   for o, n, t in relocs)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0, nsym, 0, 0))
    rawoff = 20 + 40
    relofs = rawoff + len(content)
    secblk = (b".text".ljust(8, b"\0")
              + struct.pack("<IIIIIIHHI", 0, 0, len(content), rawoff, relofs,
                            0, len(relocs), 0, 0x00100020))
    struct.pack_into("<I", hdr, 8, relofs + len(rel))
    blob = bytes(hdr) + secblk + content + rel + st.bytes()
    if pad_last:
        blob += bytes(PAGESZ * pad_last)   # raw tail padding? (invalid COFF—skip)
    open(path, "wb").write(blob)


def obj_datapad(path, ndata_pages):
    """Pad obj: .data section of n*PAGESZ zero bytes, + symbol _PADn."""
    content = bytes(PAGESZ * ndata_pages)
    st = SymTable()
    st.add(".data", 0, 1, SYM_SECTION, aux=_aux_bytes(0x00100040, content,
                                                      0, 1, 0))
    st.add("$PAD$D", 0, 1, SYM_EXTERNAL)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0,
                                len(st.recs), 0, 0))
    struct.pack_into("<I", hdr, 8, 20 + 40 + len(content))
    secblk = (b".data".ljust(8, b"\0")
              + struct.pack("<IIIIIIHHI", 0, 0, len(content), 60, 100, 0, 0,
                            0, 0x00100040))
    open(path, "wb").write(bytes(hdr) + secblk + content + st.bytes())


CASES = {
    # name: (objs, rsp_out_name)
    "c1_1pg1fix":  [[(0, [0x100])]],
    "c2_1pg3fix":  [[(0, [0x100, 0x200, 0x300])]],
    "c3_1pg17fix": [[(0, [16 * i + 4 for i in range(17)])]],
    "c4_5pg1fix":  [[(p, [0x100]) for p in range(5)]],
    "c5_5pg9fix":  [[(p, [16 * i + 4 for i in range(9)]) for p in range(5)]],
    "c6_3objs":    [[(p, [0x100]) for p in range(2)] for _ in range(3)],
    "c7_pad1":     [[(0, [0x100])], ("pad", 1)],
    "c8_pad3":     [[(0, [0x100])], ("pad", 3)],
    "c9_pad8":     [[(0, [0x100])], ("pad", 8)],
    "c10_fixatend":[[(0, [0xfdc])]],
    "c11_fixodd":  [[(0, [0x100, 0x101])]],
    "c12_9pg1fix": [[(p, [0x100]) for p in range(9)]],
    "c13_9pg9fix": [[(p, [16 * i + 4 for i in range(9)]) for p in range(9)]],
    "c14_2fix":   [[(0, [0x100, 0x104])]],
    "c15_4fix":   [[(0, [0x100, 0x104, 0x108, 0x10c])]],
    "c16_5fix":   [[(0, [0x100, 0x104, 0x108, 0x10c, 0x110])]],
    "c17_6fix":   [[(0, [0x100, 0x104, 0x108, 0x10c, 0x110, 0x114])]],
    "c18_8fix":   [[(0, [0x100 + 4*i for i in range(8)])]],
    "c19_3pg3fix":[[(p, [0x100, 0x104, 0x108]) for p in range(3)]],
    "c20_2obj3f": [[(0, [0x100, 0x104, 0x108])], [(0, [0x100, 0x104, 0x108])]],
    "c21_2pg2f":  [[(0, [0x100, 0x104])], [(0, [0x100, 0x104])]],
    "c22_zerofs": [[(0, [0x000])]],
    "c23_lastoff":[[(0, [0xffc])]],
    "c24_17fix2pg":[[(0, [16*i+4 for i in range(9)]), (1, [16*i+4 for i in range(8)])]],
    "c25_1fix1st":[[(0, [0x0])]],
    "c26_2pg1f":  [[(0, [0x100]), (1, [0x100])]],
    "c27_3pg2f":  [[(p, [0x100, 0x104]) for p in range(3)]],
    "c28_lib1":   [[(0, [0x100, 0x104])]],
    "c29_lib4":   [[(0, [0x100, 0x104])]],
    "c30_lib16":  [[(0, [0x100, 0x104])]],
    "c31_lib34":  [[(0, [0x100, 0x104])]],
}


def main():
    os.makedirs(OUT, exist_ok=True)
    rsps = []
    for name, spec in CASES.items():
        objs = []
        for i, item in enumerate(spec):
            if item[0] == "pad":
                fn = os.path.join(OUT, "%s_%d.obj" % (name, i))
                obj_datapad(fn, item[1])
            else:
                fn = os.path.join(OUT, "%s_%d.obj" % (name, i))
                obj_text_fixups(fn, item)
            objs.append(fn)
        rsp = os.path.join(OUT, "rsp_%s.rsp" % name)
        m = re.match(r"c3[01]_lib(\\d+)", name)
        libmode = re.match(r"c3[01]_lib(\d+)", name)
        with open(rsp, "w") as f:
            f.write(("/OUT:tw/%s.exe /MACHINE:IX86 /SUBSYSTEM:WINDOWS /NOLOGO "
                     "/INCREMENTAL:NO /ENTRY:swpentry\r\n" % name))
            if libmode:
                cnt = int(libmode.group(1))
                f.write("tw/lib%d.lib\r\n" % cnt)
                for i in range(cnt):
                    f.write("/INCLUDE:_LIBS%d_%d\r\n" % (cnt, i))
            f.write("build/m0/tw/entry.obj\n")
            for o in objs:
                f.write(o.replace("build/m0/tw/", "") + "\n")
        rsps.append(name)
    # entry obj: tiny .text with __swp_entry symbol + RET
    path = os.path.join(OUT, "entry.obj")
    content = b"\xc3"
    st = SymTable()
    st.add(".text", 0, 1, SYM_SECTION, aux=_aux_bytes(0x00100020, content, 0, 1, 0))
    st.add("_swpentry", 0, 1, SYM_EXTERNAL, typ=0x20)
    st.add("_ANCHOR", 0, 1, SYM_EXTERNAL)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0,
                                len(st.recs), 0, 0))
    struct.pack_into("<I", hdr, 8, 20 + 40 + len(content))
    secblk = (b".text".ljust(8, b"\0")
              + struct.pack("<IIIIIIHHI", 0, 0, len(content), 60, 100, 0, 0,
                            0, 0x00100020))
    open(path, "wb").write(bytes(hdr) + secblk + content + st.bytes())
    print("\n".join(rsps))


if __name__ == "__main__":
    main()