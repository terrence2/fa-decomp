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
                   more_syms=(), main_sym_sec=1, main_sym_cls=SYM_EXTERNAL,
                   main_relocs=()):
    """One object with a single .text contribution (original bytes) + optional
    .debug$F section carrying the lifted FPO record with a DIR32NB relocation
    to the function symbol (mirrors cl's per-function objects).

      fpo_rec -- 16-byte FPO_DATA record from FA.EXE; offStart dword zeroed,
                 patched to the final RVA by the linker's relocation.
      main_relocs -- fixup relocations for the MAIN section:
                 [(offset, target_name | None, type)]; None targets the main
                 (function) symbol itself; a name either matches func_name
                 (same symbol, chunk start) or is declared as an undefined
                 external resolved by the defining chunk obj (link resolves to
                 that chunk's VA; the stub's content dword is the addend:
                 FA_val - target_chunk_VA).
      more_sections -- [(name, flags, bytes, relocs)] appended after .text;
                 relocs = [(vaddr, symidx|None, type)] with None = main symbol.
      more_syms -- extra (name, val, sec, cls, typ, auxbytes) symbols, appended
                 after the main symbol.
    Returns whole .obj bytes."""
    secs = [(main_sec, text_flags, text_bytes, tuple(main_relocs))]
    for s in more_sections:
        secs.append(tuple(s))
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
    # resolve main-reloc target names: None/func_name -> main symbol index,
    # others become undefined externals resolved from the defining chunk obj
    # (one externals entry per distinct name keeps the table small)
    # A target that more_syms DEFINES (sec != 0, e.g. a cl-internal $L label
    # re-defined against the fitted .text) must get its defined record EARLY
    # and reuse that index for the relocs — otherwise the reloc binds to a
    # shadow undefined twin and the link reports LNK2001 even though a
    # defined duplicate exists later in the table (probed: DlgSel_fit).
    name_idx = {}
    mrel = []
    for off, tgt, typ in main_relocs:
        if tgt is None or tgt == func_name:
            mrel.append((off, None, typ))
            continue
        idx = name_idx.get(tgt)
        if idx is None:
            prior = next((s for s in more_syms if s[0] == tgt and s[2]), None)
            idx = st.add(*prior) if prior else st.add(tgt, 0, 0, SYM_EXTERNAL)
            name_idx[tgt] = idx
        mrel.append((off, idx, typ))
    mrel = tuple(mrel)
    secs[0] = (secs[0][0], secs[0][1], secs[0][2], mrel)
    for s in more_syms:
        if s[2] and s[0] in name_idx:
            continue          # already added as the reloc's defined target
        st.add(*s)
    nsym = len(st.recs)

    # assemble the file: header, 40-byte section headers (with real offsets),
    # raw payloads, relocation records, symbol table, string table
    # reloc targets: None = the main (function) symbol; int = symbol index;
    # str = a name (resolved against name_idx, else a new undefined external)
    hdr = bytearray(struct.pack("<HHIIIHH", MAGIC, len(secs), 0, 0, nsym, 0, 0))
    raw = [(c[2] if c[2] else b"") for c in secs]  # cl does not pad obj payloads
    def _ri(sym):
        if sym is None:
            return fidx
        if isinstance(sym, int):
            return sym
        idx = name_idx.get(sym)
        if idx is None:
            idx = st.add(sym, 0, 0, SYM_EXTERNAL)
            name_idx[sym] = idx
        return idx
    rel = [b"".join(struct.pack("<IIH", va, _ri(sym), typ)
                    for va, sym, typ in c[3]) for c in secs]
    nsym = len(st.recs)                        # _ri may have added externals
    struct.pack_into("<I", hdr, 12, nsym)
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


def build_group_obj(parts, extra_externals=()):
    """One object carrying MULTIPLE same-named sections (a "group" stub).

    parts -- each a dict:
      secname  section contribution name (".text"/".data"/".debug$F"/...)
      flags    section flags (align-1 etc.)
      content  contribution bytes (b"" for uninitialized CNT_*_UNINITIALIZED)
      relocs   [(off, target|None, type)]; target None = the part's owner
               symbol; a str names another symbol in this obj (part owner or
               alias) or, if unknown, an undefined external resolved by the
               defining obj.
      owner    anchor symbol defined at this contribution's start (val 0)
      aliases  extra symbols aliased to the same section: (name, typ) at val 0
               or (name, typ, val) at a section offset (merged-span inner
               chunk anchors)
      assoc    for .debug$F: 1-based index of the associated main section
    extra_externals -- (name, val, sec, cls, typ, aux) tuples appended after
    the parts' symbols (defaults: name,0,0,EXTERNAL,0,b"").

    Sections/anchors concatenate in obj order at link time, so group order in
    the link line preserves FA address order with fewer input files.
    """
    st = SymTable()
    name_idx = {}          # symbol name -> symbol index in this obj
    sec_relocs = []        # per part: [(off, idx, typ)]
    # pass 1: section symbols + defined anchors (+ aliases) in section order
    secnum_by_anchor = {}
    for i, p in enumerate(parts):
        num = i + 1
        plen = p.get("aux_len", len(p.get("content") or b""))
        st.add(p["secname"], 0, num, SYM_SECTION,
               aux=_aux_bytes(p["flags"], (b"\0" * plen if p.get("aux_len")
                                           else p.get("content") or b""),
                              len(p.get("relocs") or ()),
                              p.get("assoc") or 0, 5 if p.get("assoc") else 0))
        if p.get("assoc"):
            # .debug$F companion: references the associated main part's
            # owner symbol — don't define it again
            assert p["owner"] in name_idx, p["owner"]
            continue
        idx = st.add(p["owner"], 0, num, SYM_EXTERNAL,
                     typ=p.get("owner_typ", 0))
        name_idx[p["owner"]] = idx
        secnum_by_anchor[p["owner"]] = num
        for al in p.get("aliases") or ():
            val = al[2] if len(al) > 2 else 0
            aidx = st.add(al[0], val, num, SYM_EXTERNAL, typ=al[1])
            name_idx.setdefault(al[0], aidx)
    # pass 2: resolve reloc targets; unknown names become undefined externals
    for p in parts:
        rl = []
        for off, tgt, typ in p.get("relocs") or ():
            if tgt is None or tgt == p["owner"]:
                rl.append((off, name_idx[p["owner"]], typ))
                continue
            idx = name_idx.get(tgt)
            if idx is None:
                idx = st.add(tgt, 0, 0, SYM_EXTERNAL)
                name_idx[tgt] = idx
            rl.append((off, idx, typ))
        sec_relocs.append(rl)
    # extra symbols (e.g. additional undefined externals with class/aux)
    for s in extra_externals:
        if len(s) == 1:
            if s[0] in name_idx:
                continue
            s = (s[0], 0, 0, SYM_EXTERNAL, 0, b"")
        st.add(*s)
    nsym = len(st.recs)

    secs = [(p["secname"], p["flags"], p.get("content") or b"", sec_relocs[i])
            for i, p in enumerate(parts)]
    hdr = bytearray(struct.pack("<HHIIIHH", MAGIC, len(secs), 0, 0, nsym, 0, 0))
    raw = [c[2] for c in secs]                       # no padding, like cl
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
    for i, p in enumerate(parts):
        secblk += p["secname"].encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", p.get("sec_vsz", 0), 0, p.get("sec_rsz", len(raw[i])),
            rawptrs[i], relofs[i], 0, len(sec_relocs[i]), 0, p["flags"])
    struct.pack_into("<I", hdr, 8, off)
    return bytes(hdr) + secblk + b"".join(raw) + b"".join(rel) + st.bytes()
