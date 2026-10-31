#!/usr/bin/env python3
"""Emit direct .idata$ group objects from FA's .idata bytes (Milestone 0).

Split (load-bearing, see TODO.md):
  $2 = +0x000..0x0a0  8 import descriptors
  $3 = +0x0a0..0x0b4  null import descriptor terminator
  $4 = +0x0b4..0x42c  Import Name Table (INT/OFT)
  $5 = +0x42c..0x790  Import Address Table (IAT)  — DD12 points here
  $6 = +0x790..0x14dc hint/name strings

The linker passes content through byte-for-byte (even baked-in RVAs) and
computes DD1 = len($2)+len($3) = 0xb4 (FA) and DD12 = $5 span.

idr3 (.idata$5) additionally defines one symbol per IAT slot at its offset
("__imp__<name>" for by-name imports, "$FA$imp_<dll>_<ord>" for by-ordinal)
so that FA's 698 .text fixups pointing at IAT slots resolve by addend.
"""
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import coff

OUT = "build/idata"
IDATA_OFF = 0x11ae00          # FA .idata file offset
RANGES = [(".idata$2", 0x000, 0x0a0), (".idata$3", 0x0a0, 0x0b4),
          (".idata$4", 0x0b4, 0x42c), (".idata$5", 0x42c, 0x790),
          (".idata$6", 0x790, 0x14dc)]


def emit(k, secname, content, extra_syms=()):
    st = coff.SymTable()
    aux = coff._aux_bytes(0x00300040, content, 0, 0, 0)
    st.add(secname, 0, 1, coff.SYM_SECTION, aux=aux)
    anchor = "$FA$idata_%d" % k
    st.add(anchor, 0, 1, coff.SYM_EXTERNAL)
    for nm, val in extra_syms:
        st.add(nm, val, 1, coff.SYM_EXTERNAL)
    nsym = len(st.recs)
    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, 1, 0, 0, nsym, 0, 0))
    rawoff = 20 + 40
    secblk = secname.encode().ljust(8, b"\0") + struct.pack(
        "<IIIIIIHHI", 0, 0, len(content), rawoff, 0, 0, 0, 0, 0x00300040)
    struct.pack_into("<I", hdr, 8, rawoff + len(content))
    open(os.path.join(OUT, "idr%d.obj" % k), "wb").write(
        bytes(hdr) + secblk + content + st.bytes())


def iat_names():
    """[name or None terminator] per IAT slot, read off FA's .idata directly."""
    fa = open("FA/FA.EXE", "rb").read()
    out = []
    i, base = 0x42c, 0x18a000
    while i < 0x790:
        v, = struct.unpack_from("<I", fa, IDATA_OFF + i)
        if v == 0:
            out.append(None)
        elif v & 0x80000000:
            out.append("$FA$imp_s%d" % len(out))

        else:
            o = IDATA_OFF + (v - base)
            # hint u16 sits at o; name starts at o+2 — search for its NUL
            # from o+2 (hints < 0x100 have a zero high byte that is NOT the
            # name terminator)
            out.append(fa[o + 2:fa.index(b"\0", o + 2)].decode("latin-1"))
        i += 4
    return out


def main():
    os.makedirs(OUT, exist_ok=True)
    fa = open("FA/FA.EXE", "rb").read()
    for k, (nm, a, b) in enumerate(RANGES):
        extra = ()
        if k == 3:  # .idata$5 (IAT): define one anchor symbol per slot
            names = iat_names()
            # terminators: find owning dll's thunks to prefix a name? slot
            # symbols for terminator slots are unused by fixups — use anchors
            named = [n if n and not n.startswith("$FA$")
                     else (n or "$FA$iat_null_%d" % i)
                     for i, n in enumerate(names)]
            extra = [(("__imp__%s" % s) if not s.startswith("$FA$") else s,
                      4 * i) for i, s in enumerate(named)]
        emit(k, nm, fa[IDATA_OFF + a:IDATA_OFF + b], extra)
    n_slot = sum(1 for _ in iat_names())
    print("wrote %d objs to %s (%d IAT slots, %d by-ordinal)"
          % (len(RANGES), OUT, n_slot,
             sum(1 for n in iat_names() if n and n.startswith("$FA$"))))


if __name__ == "__main__":
    main()
