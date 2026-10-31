#!/usr/bin/env python3
"""Generate COFF stub objects from build/layout.json + FA/FA.EXE.

Every .text and .data byte of FA.EXE belongs to exactly one named or gap
chunk (peref.py); each chunk becomes one .obj whose section content is the
chunk's ORIGINAL bytes, so a stub-only link reproduces the image exactly
(unless real decompiled code replaces it — then the gate tells us what moved).

Section strategy (from microtests with link 4.20):
  .text  : PLAIN sections, align-1 flags (0x00100020) — the linker otherwise
           CC-pads every contribution to its alignment; align-1 packs tight.
  .debug$F: plain LNK_INFO section with the chunk's original FPO record;
           offStart dword zeroed, DIR32NB reloc patches it at link time.
  .data  : PLAIN initialized sections, align-8? — chunk extents are exact
           slices, so use align-1 too (0x00100040) to prevent extra padding.
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(__file__))
from peref import IMAGE_BASE
import coff

STUB_DIR = "build/stubs"


def chunk_name(c, kind):
    if c["name"]:
        return c["name"]
    return "$FA$_%s_%06x" % (kind, c["va"])


def main():
    import json
    L = json.load(open("build/layout.json"))
    exe = open("FA/FA.EXE", "rb").read()
    os.makedirs(STUB_DIR, exist_ok=True)

    # exports live at specific RVAs — their chunk symbols must NOT have stdcall
    # decoration and must match the export names exactly
    export_names = [nm for nm, _ in L["exports"]["names"]]
    exp_rvas = set(L["exports"]["rva"])

    n = 0
    manifest = []
    for c in L["text_chunks"]:
        name = chunk_name(c, "t")
        b = exe[c["off"]:c["off"] + c["size"]]
        rec = bytes.fromhex(c["fpo_rec"]) if c.get("fpo_rec") else None
        if rec is None:
            # no FPO info: emit a neutral record (EBP frame, no params)
            rec = struct.pack("<IIIHBB2x", c["va"] - IMAGE_BASE, c["size"], 0, 0, 0, 0x0)
        more_syms = []
        for em in export_names:
            if c["name"] == "_" + em:  # cl emits undecorated export aliases
                more_syms.append((em, 0, 1, coff.SYM_EXTERNAL, coff.TYPE_FUNCTION, b""))
        obj = coff.build_stub_obj(b, 0x00100020, name, fpo_rec=rec,
                                  more_syms=tuple(more_syms))
        base = "$%06x_%s" % (c["va"], ("gap_" if not c["name"] else "") + name)
        fn = os.path.join(STUB_DIR, "%03d_%s.obj" % (n, base.replace("?", "_")))
        open(fn, "wb").write(obj)
        manifest.append(dict(idx=n, file=os.path.basename(fn), va=c["va"],
                             size=c["size"], kind="text",
                             named=bool(c["name"]), fpo=c["fpo"]))
        n += 1

    for c in L["data_chunks"]:
        if c["size_file"] == 0:
            continue  # bss tail (beyond rawsz): nothing to carry (see M0 notes)
        name = chunk_name(c, "d")
        b = exe[c["off"]:c["off"] + c["size_file"]]
        obj = coff.build_stub_obj(b, 0x00100040, name, main_sec=".data")
        base = "$%06x_%s" % (c["va"], ("gap_" if not c["name"] else "") + name)
        fn = os.path.join(STUB_DIR, "d%03d_%s.obj" % (n, base.replace("?", "_")))
        open(fn, "wb").write(obj)
        manifest.append(dict(idx=n, file=os.path.basename(fn), va=c["va"],
                             size=c["size_file"], kind="data",
                             named=bool(c["name"]), fpo=False))
        n += 1

    with open(os.path.join(STUB_DIR, "manifest.json"), "w") as f:
        json.dump(manifest, f, indent=1)
    print("emitted %d stub objs to %s" % (n, STUB_DIR))


if __name__ == "__main__":
    main()