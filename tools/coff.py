#!/usr/bin/env python3
"""COFF I386 object-file reader + writer, mirroring VC4.2's cl output.

Ground truth for the writer: build/test/fpotest.obj (cl /MT /GX /O2 /Gy).
Reader: objinfo for dumping symbol/section tables (18-byte sym records),
Writer: mkstub.py uses emit to produce stub objects.
"""
import struct


def objinfo(path):
    """Dump header/sections/symbols of a COFF object file."""
    data = open(path, "rb").read()
    (mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from("<HHIIIHH", data, 0)
    print("machine=0x%x nsec=%d ts=0x%x nsyms=%d opthdr=%d chars=0x%x"
          % (mach, nsec, ts, nsym, opthsz, chars))
    off = 20 + opthsz
    secs = []
    for i in range(nsec):
        name = data[off:off + 8].rstrip(b"\0").decode()
        (vsz, va, rsz, rptr, relptr, lnnoptr, nrel, nlnno, flags) = struct.unpack_from(
            "<IIIIIIHHI", data, off + 8)
        secs.append(dict(name=name, vsz=vsz, va=va, rsz=rsz, rptr=rptr,
                         relptr=relptr, nrel=nrel, flags=flags))
        print("  sec %-8s vsz=0x%-6x va=0x%-4x rawsz=0x%-6x raw=0x%-6x rel=0x%-6x n=%-3d flags=0x%08x"
              % (name, vsz, va, rsz, rptr, relptr, nrel, flags))
        off += 40
    strtab_off = symptr + nsym * 18
    print("  strtab: %d bytes" % struct.unpack_from("<I", data, strtab_off)[0])
    SYM_AUX = {0: "NULL", 1: "AUTOMATIC", 2: "EXTERNAL", 3: "STATIC", 4: "REGISTER",
               5: "MEMBER", 6: "BLOCK", 7: "FUNC", 8: "END", 9: "FILE", 10: "UNTAG",
               11: "STRUCT", 12: "UNION", 13: "ALIAS", 14: "ARG", 20: "WEAK-EXT",
               101: "SECTION", 103: "LDSYM"}
    n = 0
    while n < nsym:
        rec = data[symptr + n * 18: symptr + (n + 1) * 18]
        if rec[:4] == b"\0\0\0\0":
            sval, = struct.unpack_from("<I", rec, 4)
            o = strtab_off + sval
            nend = data.index(b"\0", o)
            name = data[o:nend].decode("latin-1")
        else:
            name = rec[:8].rstrip(b"\0").decode("latin-1")
        val, secnum, typ = struct.unpack_from("<IHH", rec, 8)
        cls, aux = rec[16], rec[17]
        extra = ""
        if aux:
            arec = data[symptr + (n + 1) * 18: symptr + (n + 2) * 18]
            if cls == 3:  # section symbol: classic section-def aux follows
                alen, arel, alnno, acksum = struct.unpack_from("<IHHI", arec)
                asec, asel = struct.unpack_from("<HB", arec, 12)
                extra = ("AUX sec: len=0x%x nrel=%d nlnno=%d cksum=0x%x num=%d sel=%d"
                         % (alen, arel, alnno, acksum, asec, asel & 0xff))
            elif cls == 103:  # .file symbol: aux = filename string
                extra = "AUX str: %r" % arec
            else:
                extra = "AUX (sym cls=%d): %s" % (cls, arec.hex())
        print("  sym[%3d] %-24s val=0x%-6x sec=%-3d cls=%-3d aux=%d %s"
              % (n, name, val, secnum, cls, aux, extra))
        n += 1 + aux
    # relocations
    for s in secs:
        if s["nrel"]:
            print("  relocs in %s:" % s["name"])
            for i in range(s["nrel"]):
                (va, sym, typ) = struct.unpack_from("<IIH", data, s["relptr"] + i * 10)
                print("    rva=0x%-5x sym=%d typ=0x%x" % (va, sym, typ))


def aux_section(length, nrel, cksum, secnum, selection):
    """Section-definition auxiliary record (class 101 = the aux record of a
    section symbol), classic COFF layout: Length@0 nRel@4 nLnno@6 CkSum@8
    Number@12 Selection@14 pad@15."""
    return struct.pack("<IIHH", length, nrel, 0, cksum) + \
        struct.pack("<HB2x", secnum, selection) + b"\0"


# -- writer: mirrors cl 10.20's object layout (ground truth = objinfo dump) --

MAGIC = 0x14C  # IMAGE_FILE_MACHINE_I386

SYM_SECTION = 3      # storage class of section-definition symbols
SYM_EXTERNAL = 2     # storage class of function/global definitions
TYPE_FUNCTION = 0x20
SEC_DEBUG = -2       # pseudo section number for .file symbols (0xFFFE)

S_TEXT_COMDAT = 0x60501020   # CNT_CODE|ALIGN_16BYTES|LNK_COMDAT|MEM_READ|MEM_EXECUTE
S_TEXT_PLAIN = 0x50500020    # same, minus LNK_COMDAT
S_DEBUGF = 0x42101048        # cl's exact .debug$F flags (COMDAT form)
S_DEBUGF_PLAIN = 0x42100048  # same, minus LNK_COMDAT
S_DATA_PLAIN = 0xC0300040    # READ|WRITE|ALIGN_8|CNT_INITIALIZED_DATA (cl's)

RELOC_DIR32 = 0x6     # IMAGE_REL_I386_DIR32
RELOC_DIR32NB = 0x7   # IMAGE_REL_I386_DIR32NB (image-base-relative, for FPO)
RELOC_REL32 = 0x14    # IMAGE_REL_I386_REL32


class SymTable:
    """COFF symbol/string table accumulator. Aux records interleave directly
    after their owning symbol, as cl emits them."""

    def __init__(self):
        self.recs = []   # 18-byte records: symbols, with aux right after
        self.strtab = b""

    def _stridx(self, name):
        nb = name.encode("latin-1") + b"\0"
        off = 4 + len(self.strtab)
        self.strtab += nb
        return off

    def add(self, name, val, sec, cls, typ=0, aux=b""):
        nb = name.encode("latin-1") + b"\0"
        if len(nb) <= 8:
            field = nb.ljust(8, b"\0")
        else:
            field = b"\0\0\0\0" + struct.pack("<I", self._stridx(name))
        idx = len(self.recs)
        self.recs.append(field + struct.pack("<IHHBB", val, sec & 0xFFFF, typ, cls, 1 if aux else 0))
        if aux:
            assert len(aux) == 18, len(aux)
            self.recs.append(aux)
        return idx

    def add_section(self, name, length, nrel, cksum, num, selection):
        """Section-definition symbol + its aux record."""
        aux = struct.pack("<IIHH", length, nrel, 0, cksum) + \
            struct.pack("<HB2x", num, selection) + b"\0"
        return self.add(name, 0, 0, SYM_SECTION, aux=aux)

    def bytes(self):
        return b"".join(self.recs) + struct.pack("<I", 4 + len(self.strtab)) + self.strtab


def build_stub_obj(text_bytes, text_flags, func_name, fpo_rec=None,
                   debugf_assoc=False, main_sec=".text", more_sections=(),
                   more_syms=(), main_sym_sec=1, main_sym_cls=SYM_EXTERNAL):
    """One object with a single .text contribution (original bytes) + optional
    .debug$F section carrying the lifted FPO record with a DIR32NB relocation
    to the function symbol (mirrors cl's per-function objects).

      fpo_rec -- 16-byte FPO_DATA record from FA.EXE; offStart dword zeroed,
                 patched to the final RVA by the linker's relocation.
      more_sections -- [(name, flags, bytes, relocs)] appended after .text;
                 relocs = [(vaddr, symidx|None, type)] with None = main symbol.
      more_syms -- extra (name, val, sec, cls, typ, auxbytes) symbols, appended
                 after the main symbol.
    Returns whole .obj bytes."""
    secs = [(main_sec, text_flags, text_bytes, ())] + list(more_sections)
    if fpo_rec is not None:
        dbgflags = S_DEBUGF if debugf_assoc else S_DEBUGF_PLAIN
        secs.append((".debug$F", dbgflags, b"\0\0\0\0" + fpo_rec[4:],
                     ((0, None, RELOC_DIR32NB),)))

    st = SymTable()
    # section symbols first, in section order (cl's order); aux bytes carry
    # the real content length and relocation count so the linker sees it too
    for i, (nm, flags, content, relocs) in enumerate(secs):
        comdat = flags & 0x1000  # LNK_COMDAT
        sel = 1 if (i == 0 and comdat) else (5 if i else 0)  # any | assoc | none
        num = 1 if i else 0              # .debug$F associates with .text (sec 1)
        st.add(nm, 0, i + 1, SYM_SECTION,
               aux=_aux_bytes(flags, content, len(relocs), num, sel))
    # the main function symbol lives in the main section (= 1)
    fidx = st.add(func_name, 0, main_sym_sec, main_sym_cls, typ=TYPE_FUNCTION)
    for s in more_syms:
        st.add(*s)
    nsym = len(st.recs)

    # assemble the file: header, 40-byte section headers (with real offsets),
    # raw payloads, relocation records, symbol table, string table
    hdr = bytearray(struct.pack("<HHIIIHH", MAGIC, len(secs), 0, 0, nsym, 0, 0))
    raw = [(c[2] if c[2] else b"") for c in secs]  # cl does not pad obj payloads
    rel = [b"".join(struct.pack("<IIH", va, fidx if sym is None else sym, typ)
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
    for i, (nm, flags, content, relocs) in enumerate(secs):
        secblk += nm.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(raw[i]),
            rawptrs[i], relofs[i], 0, len(relocs), 0, flags)
    symoff = off
    struct.pack_into("<I", hdr, 8, symoff)    # PointerToSymbolTable @8
    return bytes(hdr) + secblk + b"".join(raw) + b"".join(rel) + st.bytes()


def _aux_bytes(flags, content, nrel, secnum, sel):
    clen = len(content)  # unpadded, like cl
    return struct.pack("<IIHH", clen, nrel, 0, 0) + \
        struct.pack("<HB2x", secnum, sel) + b"\0"
