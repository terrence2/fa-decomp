#!/usr/bin/env python3
"""Build direct .idata$ group objs from FA's .idata bytes, split
$2=0xa0 (8 descs), $3=0x14 (null import descriptor), $4=+0xb4..0x42c (INT),
$5=0x42c..0x790 (IAT), $6=0x790..0x14dc (hint/name strings)."""
import struct, sys
sys.path.insert(0, "tools")
import coff

fa = open("FA/FA.EXE", "rb").read()
IDATA_OFF = 0x11ae00
RANGES = [(".idata$2", 0x000, 0x0a0), (".idata$3", 0x0a0, 0x0b4),
          (".idata$4", 0x0b4, 0x42c), (".idata$5", 0x42c, 0x790),
          (".idata$6", 0x790, 0x14dc)]

for k, (nm, a, b) in enumerate(RANGES):
    content = fa[IDATA_OFF + a:IDATA_OFF + b]
    st = coff.SymTable()
    aux = coff._aux_bytes(0x00300040, content, 0, 0, 0)
    st.add(nm, 0, 1, coff.SYM_SECTION, aux=aux)
    st.add("$FA$idata_%d" % k, 0, 1, coff.SYM_EXTERNAL)
    nsym = len(st.recs)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0, nsym, 0, 0))
    rawoff = 20 + 40
    secblk = nm.encode().ljust(8, b"\0") + struct.pack(
        "<IIIIIIHHI", 0, 0, len(content), rawoff, 0, 0, 0, 0, 0x00300040)
    symoff = rawoff + len(content)
    struct.pack_into("<I", hdr, 8, symoff)
    open("build/m0/idr%d.obj" % k, "wb").write(
        bytes(hdr) + secblk + content + st.bytes())
print("rebuilt idr0..idr4 with linker-semantic split")
