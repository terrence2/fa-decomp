#!/usr/bin/env python3
"""Probe 2: per-function .text sections, PLAIN align-1 flags (0x00100020),
alternate WITH / WITHOUT a .debug$F companion.  Hypothesis: LINK aligns a
section to 16 (lea-family filler, like FA) iff it has an associated .debug$F
record, and extends the PREVIOUS record's cbProcSize to cover the pad;
sections without .debug$F butt directly (matches FA's EBP-frame functions)."""
import struct
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
sys.path.insert(0, "tools")
import struct as _st

import coff

# VC4.2 section-def aux (hex-proven vs padcl.obj):
#   ln(4)@0 nrel(4)@4 nln(2)@8 pad(2)@10 Number(2)@12 Selection(1)@14 pad(3)@15
FAUX = lambda ln, nrel, num, sel: (
    _st.pack("<IIIHB", ln, nrel, 0, num, sel) + b"\0\0\0")

TEXTF = 0x00101020       # align-1: hypothesis test
DBGF = 0x42101048        # cl's .debug$F flags (from padcl dump)

# (label, size, has_debugf) - FPO'd first, then interleaved; entry = first
UNITS = [("a", 0x11, True),    # next FPO'd: 5 bytes to 16
         ("b", 0x0c, True),    # next FPO'd: 4
         ("c", 0x07, False),   # next NO debug: butt directly
         ("d", 0x09, True),    # next FPO'd: 7
         ("e", 0x12, False),   # next NO debug
         ("f", 0x1b, True),    # next FPO'd: 5 (05 00 00 00 00?)
         ("g", 0x0e, True)]    # last: 2 to boundary
fn = lambda u: "_w" + u


def build():
    st = coff.SymTable()
    secs, fidx = [], {}
    order = []
    secno = 0                          # = current section-table position
    for u, sz, dbg in UNITS:
        secno += 1                       # .text section number
        textno = secno
        st.add(".text$%s" % u, 0, secno, coff.SYM_SECTION, aux=FAUX(sz, 0, 0, 1))   # coff.py convention: num=0 sel=1
        idx_fn = len(st.recs)
        st.add(fn(u), 0, secno, coff.SYM_EXTERNAL, typ=coff.TYPE_FUNCTION)
        secs.append((".text$%s" % u, TEXTF, b"\xc3" * sz, ()))
        fidx[fn(u)] = idx_fn
        if dbg:
            # 16-byte FPO_DATA: OffStart(4, reloc-patched) + cbProcSize + 8B
            rec = b"\0" * 4 + struct.pack("<I", sz) + b"\0" * 8
            secno += 1                   # .debug$F takes the NEXT section slot
            st.add(".debug$F", 0, secno, coff.SYM_SECTION, aux=FAUX(len(rec), 1, textno, 5))
            secs.append((".debug$F", DBGF, b"\0\0\0\0" + rec[4:],
                         ((0, idx_fn, coff.RELOC_DIR32NB),)))
        order.append(fn(u))
    secno += 1
    st.add(".data", 0, secno, coff.SYM_SECTION,
           aux=FAUX(4 * len(order), len(order), 0, 0))
    secs.append((".data", 0x00400040, b"".join(struct.pack("<I", 0) for u in order),
                 tuple((4 * i, fidx[u], coff.RELOC_DIR32NB)
                       for i, u in enumerate(order))))

    hdr = bytearray(struct.pack("<HHIIIHH", coff.MAGIC, len(secs), 0, 0,
                                len(st.recs), 0, 0))
    raw = [c[2] for c in secs]
    rel = [b"".join(struct.pack("<IIH", va, sym, typ)
                    for va, sym, typ in c[3]) for c in secs]
    rawoff = 20 + 40 * len(secs)
    rawptrs, off = [], rawoff
    for b in raw:
        rawptrs.append(off if b else 0)
        off += len(b)
    relofs = []
    for b in rel:
        relofs.append(off if b else 0)
        off += len(b)
    secblk = b""
    for i, (nm, flags, content, rels_) in enumerate(secs):
        secblk += nm.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(raw[i]), rawptrs[i], relofs[i], 0,
            len(rels_), 0, flags)
    struct.pack_into("<I", hdr, 8, off)
    return bytes(hdr) + secblk + b"".join(raw) + b"".join(rel) + st.bytes()


if __name__ == "__main__":
    out = sys.argv[1] if len(sys.argv) > 1 else "build/probe/pads/probe2.obj"
    open(out, "wb").write(build())
    for u, sz, dbg, *_ in UNITS:
        print("  %s sz=0x%-3x dbg=%s" % (fn(u), sz, dbg))