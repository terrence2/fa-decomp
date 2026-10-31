#!/usr/bin/env python3
"""Generate COFF stub group-objects from build/layout.json + FA/FA.EXE.

Every .text and .data byte of FA.EXE belongs to exactly one named or gap
chunk (peref.py); GROUP_SIZE consecutive chunks become one .obj with one
section per chunk (original bytes). Grouping matters because /EXPORT makes
link 4.20 spawn `LINK /lib` with ALL input objects as argv — the 32k-char
command line truncates around input #700, so 4,900+ files cannot work
(lnk2 session: "LNK1181 ../stubs/693_..." → LNK1141). Obj/section order in
the link line preserves FA's address order either way.

Fixup relocations (build/reloc_map.json, from FA's .reloc table):
  stubs zero every fixup dword and emit a DIR32 reloc anchored on the TARGET
  chunk's symbol with addend = FA_val - target_chunk_VA (anchors.py; link
  4.20 writes final = symaddr + addend). The linker then regenerates .reloc
  from these relocs byte-identically.

Sections per chunk (see build/m0 microtests):
  .text   : PLAIN align-1 (0x00100020) + companion .debug$F (plain, 0x42100048)
            holding the original FPO record, offStart zeroed, DIR32NB reloc.
            Only for chunks whose record EXISTS in FA's FPO payload (linker
            collects .debug$F into that payload under /DEBUG; FA's payload
            has no record for the 0x1000/0x175 chunk) — gap chunks (no
            record) get no .debug$F either.
  .data   : PLAIN initialized align-1 (0x00100040).
  .bss    : chunk CNT_UNINITIALIZED (cl's ground-truth .bss section,
            align1; merges into image .data and extends its vsz) in a
            dedicated group, after a filler for the raw-window tail gap.
            The header SizeOfRawData must carry the extent (link 4.20 keys
            on it — aux-only length is silently dropped; probed
            build/m0/rd/bs_hdr.exe).
"""
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from anchors import Anchors
from peref import IMAGE_BASE
import coff

STUB_DIR = os.environ.get("STUB_DIR", "build/stubs")
GROUP_SIZE = int(os.environ.get("GROUP_SIZE", "50"))  # chunk sections per group obj
# Comma-separated absolute VAs whose chunks become singleton group objs
# (cut the batch before and after) — lets a decompiled object replace one
# chunk at its exact rsp position (tools/mkrsp.py --replace).
SPLIT_AT = {int(x, 0) for x in
            os.environ.get("SPLIT_AT", "").split(",") if x.strip()}
BSS_GROUP_SIZE = 200      # bss sections are tiny; batch more per obj
BSS_FLAGS = 0xC0100080    # READ|WRITE|ALIGN_1|CNT_UNINITIALIZED (cl emits .bss
                          # 0xC0400080; align must be 1 so chunk sizes tile
                          # without linker padding)


def text_parts(name, c, content, relocs, rec, aliases, want_dbg):
    """Parts for one .text chunk: code section + FPO .debug$F companion."""
    main = dict(secname=".text", flags=0x00100020, content=content,
                relocs=relocs, owner=name, owner_typ=coff.TYPE_FUNCTION)
    if aliases:
        main["aliases"] = [(a, coff.TYPE_FUNCTION) for a in aliases]
    if rec is None or not want_dbg:
        return main, None
    dbg = dict(secname=".debug$F", flags=coff.S_DEBUGF_PLAIN,
               content=b"\0\0\0\0" + rec[4:],
               relocs=[(0, name, coff.RELOC_DIR32NB)],
               owner=name, assoc=None)
    return main, dbg


def fa_fpo_records():
    """(offStart, cbProcSize) tuples of FA's FPO payload records. The payload
    is 2986 plain 16-byte records — there is NO 16-byte header (the first
    record is the chunk at .text start 0x1000/0x175, which FA's dir entry
    size 0xbaa0 = 2986*16 confirms)."""
    fa = open("FA/FA.EXE", "rb").read()
    pay = fa[0x131b10:0x13d5b0]      # FPO payload file range
    return [struct.unpack_from("<II", pay, 16 * i) for i in range(len(pay) // 16)]


def main():
    L = json.load(open("build/layout.json"))
    rm = json.load(open("build/reloc_map.json"))
    exe = open("FA/FA.EXE", "rb").read()
    os.makedirs(STUB_DIR, exist_ok=True)
    A = Anchors(L)
    export_names = [nm for nm, _ in L["exports"]["names"]]
    fpo_set = set(fa_fpo_records())
    unres = []
    n_stub_fixups = [0]

    def fixup_relocs(chunk, kind, data_off, n_bytes):
        """[(offset, anchor_name, DIR32)] with host dwords zeroed in place."""
        key = str(chunk["va"])  # reloc_map.json keys are absolute chunk VAs
        offs = rm["text" if kind == "t" else "data"].get(key, [])
        content = bytearray(exe[data_off:data_off + n_bytes])
        relocs = []
        for os_ in offs:
            o = int(os_)
            v = struct.unpack_from("<I", bytes(content), o)[0]
            an = A.anchor(v) if v else None
            if an is None:
                unres.append((hex(v), key))
                continue
            addend = (v - an[1]) & 0xFFFFFFFF
            struct.pack_into("<I", content, o, addend)
            relocs.append((o, an[0], coff.RELOC_DIR32))
        n_stub_fixups[0] += len(relocs)
        return bytes(content), relocs

    manifest = []
    idx = 0

    def write_group(idx, base, obj, kind, batch, nfixups):
        fn = os.path.join(STUB_DIR, base)
        open(fn, "wb").write(obj)
        manifest.append(dict(idx=idx, file=os.path.basename(fn), kind=kind,
                             va=batch["first_va"], vae=batch["last_va"],
                             size=len(obj), chunks=batch["n"],
                             nfixups=nfixups))

    # ---- .text groups (VA order) ----
    batch = {"n": 0}
    batch["parts"] = partlist = []
    recs = []

    def add_text(c):
        name = A.chunk_name(c, "t")
        aliases = ([c["name"][1:]]
                   if c["name"] and c["name"][1:] in export_names else [])
        content, relocs = fixup_relocs(c, "t", c["off"], c["size"])
        rec = bytes.fromhex(c["fpo_rec"]) if c.get("fpo_rec") else None
        if rec is None:
            rec = struct.pack("<IIIHBB2x", c["va"] - IMAGE_BASE, c["size"],
                              0, 0, 0, 0)
        else:
            # record rva/size sanity: must match the chunk it rides on
            rva, sz = struct.unpack_from("<II", rec)
            assert (rva, sz) == (c["va"] - IMAGE_BASE, c["size"]), \
                (hex(rva), hex(sz), hex(c["va"]))
        want_dbg = (c["va"] - IMAGE_BASE, c["size"]) in fpo_set \
            and os.environ.get("NO_FPO") != "1"
        main, dbg = text_parts(name, c, content, relocs, rec, aliases, want_dbg)
        partlist.append(main)                      # main sections in order
        if dbg is not None:
            recs.append((partlist.index(main), dbg))   # fix .debug$F assoc later

    def flush_text():
        for i, (mi, dbg) in enumerate(recs):
            dbg["assoc"] = mi + 1                  # 1-based main-section num
            partlist.append(dbg)
        obj = coff.build_group_obj(partlist)
        write_group(idx, "g%04d_$%06x.obj" % (idx, batch["first_va"]),
                    obj, "textgroup", batch, batch.get("nfixups", 0))

    for c in L["text_chunks"]:
        if c["va"] in SPLIT_AT and batch["n"]:
            flush_text()
            batch = {"n": 0, "parts": (partlist := [])}
            recs = []
        if batch["n"] == 0:
            batch["first_va"] = c["va"]
            batch["nfixups"] = 0
        add_text(c)
        batch["n"] += 1
        batch["nfixups"] += len(partlist[-1]["relocs"])
        batch["last_va"] = c["va"]
        if batch["n"] == GROUP_SIZE or c["va"] in SPLIT_AT:
            flush_text()
            batch = {"n": 0, "parts": (partlist := [])}
            recs = []
    if batch["n"]:
        flush_text()

    # ---- .data file-backed groups (skip zero-extent dup entries) ----
    # One chunk (e.g. ?ifmPalette@@3PAUT_RGB@@A at 0x51c390) straddles the
    # .data raw window end (0x11c400): its extent exceeds its file bytes by a
    # zero tail. Init contributions therefore cover only [va0, raw_end);
    # a filler .bss part bridges [raw_end, first bss va) so the .bss
    # concatenation lands each bss chunk at its exact FA VA.
    datas = [c for c in L["data_chunks"] if c["size_file"] != 0 and
             c["size_full"] == c["size_file"]]
    straddler = next((c for c in L["data_chunks"]
                      if c["size_file"] != 0 and c["size_full"] > c["size_file"]), None)
    for gi in range(0, len(datas), GROUP_SIZE):
        bd = datas[gi:gi + GROUP_SIZE]
        nfix = 0
        parts = []
        for c in bd:
            content, relocs = fixup_relocs(c, "d", c["off"], c["size_file"])
            nfix += len(relocs)
            parts.append(dict(secname=".data", flags=0x00100040,
                              content=content, relocs=relocs,
                              owner=A.chunk_name(c, "d")))
        if straddler and gi + GROUP_SIZE > len(datas) - 1:  # last group: append straddler's file part
            c = straddler
            content, relocs = fixup_relocs(c, "d", c["off"], c["size_file"])
            nfix += len(relocs)
            parts.append(dict(secname=".data", flags=0x00100040,
                              content=content, relocs=relocs,
                              owner=A.chunk_name(c, "d")))
        obj = coff.build_group_obj(parts)
        last = bd[-1] if not (straddler and gi + GROUP_SIZE > len(datas) - 1) else straddler
        write_group(idx, "d%04d_$%06x.obj" % (idx, bd[0]["va"]),
                    obj, "datagroup", {"first_va": bd[0]["va"],
                                       "last_va": last["va"],
                                       "n": len(bd) + (1 if last is straddler else 0)}, nfix)
        idx += 1

    # ---- .bss groups (extent-only, VA order; merge into image .data) ----
    # Probed (build/m0/pb/bimg.exe via cl ground truth bss.obj): link 4.20
    # merges ".bss" CNT_UNINITIALIZED sections into the image .data and
    # extends its vsz; ".data"-named uninit sections are DROPPED (LNK4078).
    bss = [c for c in L["data_chunks"]
           if c["size_file"] == 0 and c["size_full"] != 0]
    dva = next(s["va"] for s in L["secs"] if s["name"] == ".data")
    gap_end = IMAGE_BASE + dva + sum(c["size_file"] for c in datas) + \
        (straddler["size_file"] if straddler else 0)
    filler = bss[0]["va"] - gap_end if bss else 0
    assert filler >= 0, (hex(gap_end), hex(bss[0]["va"]))
    for gi in range(0, len(bss), BSS_GROUP_SIZE):
        bd = bss[gi:gi + BSS_GROUP_SIZE]
        parts = []
        if gi == 0 and filler:
            parts.append(dict(secname=".bss", flags=BSS_FLAGS, content=b"",
                              aux_len=filler, relocs=(),
                              owner="$FA$_bss_pad", sec_rsz=filler))
            parts[0]["owner_typ"] = 0
        parts += [dict(secname=".bss", flags=BSS_FLAGS, content=b"",
                       aux_len=c["size_full"], relocs=(),
                       owner=A.chunk_name(c, "d"),
                       sec_rsz=c["size_full"]) for c in bd]
        obj = coff.build_group_obj(parts)
        write_group(idx, "b%04d_$%06x.obj" % (idx, bd[0]["va"]),
                    obj, "bssgroup", {"first_va": bd[0]["va"],
                                      "last_va": bd[-1]["va"],
                                      "n": len(bd)}, 0)
        idx += 1

    with open(os.path.join(STUB_DIR, "manifest.json"), "w") as f:
        json.dump(manifest, f, indent=1)
    print("emitted %d group objs (%d fixup relocs) to %s"
          % (len(manifest), n_stub_fixups[0], STUB_DIR))
    if unres:
        print("UNRESOLVED anchors: %d e.g. %s" % (len(unres), unres[:5]))


if __name__ == "__main__":
    main()