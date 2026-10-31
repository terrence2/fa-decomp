#!/usr/bin/env python3
"""Emit the .rdata literal-region stub (Milestone 0).

FA .rdata layout: [debug dir 0x54 — linker-generated under /DEBUG]
                  [app+CRT region 0x139c — THIS stub, 0xe5054..0xe63f0]
                  [export dir 0x62 — linker-generated from /EXPORT]

Probed (build/m0/rd/rd030.exe): the obj .rdata contribution must carry the
WRITE bit or link 4.20 splits it into a second image .rdata (LNK4078);
image flags come out 40000040 regardless. Obj contributions land first in
address order, the /EXPORT-synthesized export dir last (FA: 0xe63f0 ✓).

No-/DEBUG mode (round 2): the stub carries FA's whole [0, 0x13f0) — the 0x54
debug-dir bytes COPIED (no fixups target them; dir[6] payload pointers stay
wrong until the /DEBUG round) + the 0x139c region with its 168 fixup relocs.
With /DEBUG the content starts at 0x54 and the linker regenerates the dir.
"""
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from anchors import Anchors
from peref import IMAGE_BASE
import coff

RDATA_RAW = 0xe4400
REGION = (0x54, 0x13f0)   # .rdata-relative (debug dir [0,0x54); export dir at 0x13f0+)
RD_FLAGS = 0x40300040     # WRITE bit required to merge with the synth .rdata


def emit(path="build/idata/rdata.obj", dir_in_stub=True):
    """dir_in_stub=True (round 2, no /DEBUG): content covers [0, 0x13f0) with
    FA's debug-dir bytes copied at the front. False (final /DEBUG round):
    content covers [0x54, 0x13f0); the linker generates the dir itself."""
    exe = open("FA/FA.EXE", "rb").read()
    rm = json.load(open("build/reloc_map.json"))
    L = json.load(open("build/layout.json"))
    A = Anchors(L)
    a, b = REGION
    content = bytearray(exe[RDATA_RAW + (0 if dir_in_stub else a):RDATA_RAW + b])
    fixoff = 0 if dir_in_stub else a
    relocs = []
    unres = 0
    for r, typ in rm["rdata"]:
        if not (a <= r - 0xe5000 < b):
            continue
        o = r - 0xe5000 - fixoff
        v = struct.unpack_from("<I", bytes(content), o)[0]
        an = A.anchor(v)
        if an is None:
            unres += 1
            continue
        struct.pack_into("<I", content, o, (v - an[1]) & 0xFFFFFFFF)
        relocs.append((o, an[0], coff.RELOC_DIR32))
    st = coff.SymTable()
    aux = coff._aux_bytes(RD_FLAGS, bytes(content), len(relocs), 0, 0)
    st.add(".rdata", 0, 1, coff.SYM_SECTION, aux=aux)
    # the anchor sits at the REGION start (0xe5054), i.e. +0x54 into the
    # section content when the copied debug dir leads it
    st.add("$FA$rdata0", 0x54 if dir_in_stub else 0, 1, coff.SYM_EXTERNAL)
    # ALL symbol-table additions must complete before nsym is captured
    idxs = []
    for _o, nm, _t in relocs:
        idxs.append(2 if nm == "$FA$rdata0"
                    else st.add(nm, 0, 0, coff.SYM_EXTERNAL))
    nsym = len(st.recs)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0, nsym, 0, 0))
    rawoff = 20 + 40
    relofs = rawoff + len(content)
    rel = b"".join(struct.pack("<IIH", o, idx, t)
                   for (o, n, t), idx in zip(relocs, idxs))
    secblk = b".rdata".ljust(8, b"\0") + struct.pack(
        "<IIIIIIHHI", 0, 0, len(content), rawoff, relofs, 0, len(relocs), 0,
        RD_FLAGS)
    struct.pack_into("<I", hdr, 8, relofs + len(rel))
    open(path, "wb").write(bytes(hdr) + secblk + bytes(content) + rel +
                           st.bytes())
    print("wrote %s: 0x%x bytes, %d relocs, %d unresolved" %
          (path, b - a, len(relocs), unres))
if __name__ == "__main__":
    emit(dir_in_stub="--with-dir" in sys.argv)
