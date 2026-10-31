#!/usr/bin/env python3
"""Craft a .RES from FA.EXE's .rsrc leaf blobs (Milestone 0).

FA's .rsrc (RVA 0x18c000, file 0x11c400, 0x1200 raw / 0x1184 vsz):
  ROOT            ts 0x33ef9c9b ver (0,4)
   TYPE 3 ICON    ts 0x33ef9c9b ver (0,2)
     ID 1          ver (0,1) lang 0x409 leaf @0x160 size 0x2e8
     ID 2          ver (0,1) lang 0x409 leaf @0x448 size 0x8a8
   TYPE 5 DIALOG  ver (0,2)  ID 111 ver (0,1) lang 0x409 leaf @0xd14 0xf6
   TYPE 14 GROUP_ICON ver(0,2) ID 103 ver(0,1) lang 0x409 leaf @0xcf0 0x22
   TYPE 16 VERSION ver(0,2)  ID 1   ver(0,1) lang 0x409 leaf @0xe0c 0x378
Leaf storage [0x160..0x1184) contiguous: icon1, icon2, groupicon, dialog,
version. Dirs+leaf entries [0, 0x160), raw pad [0x1184, 0x1200).

RES format (16-byte pre-header per block + block body):
  block = (u32 dataSize, u32 hdrSize, dword typeID, dword nameID,
           u32 dataVersion, u16 memFlags, u16 langID)  + optional ordinal/
  string bodies  (ordinal dword: low word 0xFFFF, high word = ordinal)
  then data, padded to 4.
A leading null block ("dir" = 32 bytes: dataSize 0, hdrSize 32, both
0xFFFF0000 ordinals 0, version 0, flags 0) starts the file.
"""
import struct
import sys
import os

RVA, RAW, SZ = 0x18c000, 0x11c400, 0x1200
LEAVES = [
    ("icon", 3, 1, 0x160, 0x2e8),
    ("icon", 3, 2, 0x448, 0x8a8),
    ("group_icon", 14, 103, 0xcf0, 0x22),
    ("dialog", 5, 111, 0xd14, 0xf6),
    ("version", 16, 1, 0xe0c, 0x378),
]
LANG = 0x409
MEMFLAGS = 0x1030          # MOVEABLE|DISCARDABLE|PURE?? — probe constant
RCDATA_RVA = 0x18c000


def extract(exe):
    out = []
    for _nm, typ, rid, roff, rsz in LEAVES:
        fo = RAW + roff
        out.append((typ, rid, exe[fo:fo + rsz]))
    return out


def res_block(typ, rid, blob, memflags, lang, version):
    """Full 32-byte RES data header:
    dataSize, hdrSize=32, typeID, nameID, dataVersion, memFlags, langID,
    version, characteristics. Integer type/name IDs are stored as
    0xFFFF in the LOW word with the ordinal in the HIGH word (the 0x8000
    form is the .rsrc-directory entry, not .RES)."""
    hdr = struct.pack("<IIIIIHHII", len(blob), 32,
                      0xFFFF | (typ << 16), 0xFFFF | (rid << 16),
                      0, memflags, lang, version, 0)
    return hdr, blob
    return hdr, blob


def build(path="FA.res"):
    exe = open("FA/FA.EXE", "rb").read()
    root = struct.pack("<IIIIIHHII", 0, 32, 0xFFFF, 0xFFFF, 0, 0x0000, 0, 0, 0)
    with open(path, "wb") as fp:
        fp.write(root)
        for typ, rid, blob in extract(exe):
            (hdr, blob) = res_block(typ, rid, blob, MEMFLAGS, LANG, 0x00010000)
            fp.write(hdr)
            fp.write(blob)
            fp.write(b"\0" * ((4 - len(blob) % 4) % 4))
    print("wrote %s (%d blocks)" % (path, len(LEAVES) + 1))


if __name__ == "__main__":
    os.mkfifo if False else None
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    build(sys.argv[1] if len(sys.argv) > 1 else "FA.res")