#!/usr/bin/env python3
"""Anchor-symbol resolution for FA fixup relocations.

link 4.20 writes final = target_symbol_VA + baked addend for DIR32 relocs
(probed: build/m0/d32.exe). A stub obj therefore reproduces FA's exact fixup
value by anchoring the reloc on the symbol at the TARGET chunk's start, with
addend = FA_val - target_chunk_VA, and the host content dwords zeroed.

Target classes (from build/reloc_tgts.json):
  .text  its chunk symbol (FA.SMS name or $FA$_t_<va> gap anchor)
  .data  its chunk symbol (file-backed or BSS chunk; bss handled via
         CNT_UNINITIALIZED .data stubs)
  .rdata $FA$rdata0       (single literal region 0xe5054..0xe63f0)
  .idata IAT slot symbols defined in the .idata$5 group obj
"""
import bisect
import struct


class Anchors:
    def __init__(self, layout, idata_va=0x18a000, rdata_anchor=0xe5054):
        self.L = L = layout
        self.idata_va = idata_va
        self.rdata_va = 0x400000 + rdata_anchor
        self._tc = sorted(L["text_chunks"], key=lambda c: c["va"])
        self._dc = sorted(L["data_chunks"], key=lambda c: c["va"])
        self._tk = [c["va"] for c in self._tc]
        self._dk = [c["va"] for c in self._dc]
        self._secs = sorted(L["secs"], key=lambda s: s["va"])
        # IAT slot table: absolute slot VA -> symbol name
        fa = open("FA/FA.EXE", "rb").read()
        ID = 0x11ae00
        self.iat = []
        for i in range(0x42c, 0x790, 4):
            v, = struct.unpack_from("<I", fa, ID + i)
            if v == 0:
                nm = "$FA$iat_null_%d" % ((i - 0x42c) // 4)
            elif v & 0x80000000:
                nm = "$FA$imp_s%d" % ((i - 0x42c) // 4)
            else:
                o = ID + (v - idata_va)
                nm = "__imp__" + fa[o + 2:fa.index(b"\0", o + 2)].decode("latin-1")
            self.iat.append(nm)
        self.slot_va = {0x400000 + idata_va + 0x42c + 4 * i: nm
                        for i, nm in enumerate(self.iat)}

    def _chunk(self, chunks, keys, va):
        i = bisect.bisect_right(keys, va) - 1
        if i < 0:
            return None
        c = chunks[i]
        sz = c.get("size", c.get("size_full"))
        if c["va"] <= va < c["va"] + sz:
            return c
        return None

    @staticmethod
    def chunk_name(c, kind):
        return c["name"] or "$FA$_%s_%06x" % (kind, c["va"])

    def host_sec(self, va):
        rva = va - 0x400000
        for s in self._secs:
            if s["va"] <= rva < s["va"] + max(s["vsz"], s["rawsz"]):
                return s["name"]
        return None

    def anchor(self, t):
        """(symbol_name, symbol_final_va) anchoring absolute VA t, or None."""
        name = self.host_sec(t)
        if name == ".text":
            c = self._chunk(self._tc, self._tk, t)
            return (self.chunk_name(c, "t"), c["va"]) if c else None
        if name == ".data":
            c = self._chunk(self._dc, self._dk, t)
            return (self.chunk_name(c, "d"), c["va"]) if c else None
        if name == ".rdata":
            return ("$FA$rdata0", self.rdata_va)
        if name == ".idata":
            nm = self.slot_va.get(t)
            return (nm, t) if nm else None
        return None