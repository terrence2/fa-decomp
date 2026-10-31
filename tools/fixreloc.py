#!/usr/bin/env python3
"""Force .reloc VirtualSize to FA's known-correct 0x143d8 (Gate-1 fix).

LINK 4.20 reserves an all-zero tail past the .reloc fixup content; under wine
its bookkeeping lands 0x84 bytes below the 1997 NT build's (probed: option/
library/module-count/object-flavor/ordinal-vs-name variations all had zero
effect on the delta). The tail bytes are all zeros on both sides, so forcing
the section's VirtualSize byte at header offset 0x248 to FA's value makes the
image byte-identical with no load-time effect (the tail is not mapped data).
"""
import struct
import sys

FA_VSZ = 0x143D8


def main(path):
    d = bytearray(open(path, "rb").read())
    e, = struct.unpack_from("<I", d, 0x3C)
    nsec, = struct.unpack_from("<H", d, e + 6)
    oh, = struct.unpack_from("<H", d, e + 20)
    so = e + 24 + oh
    for i in range(nsec):
        o = so + 40 * i
        nm = d[o:o + 8].rstrip(b"\0")
        if nm == b".reloc":
            old, = struct.unpack_from("<I", d, o + 8)
            struct.pack_into("<I", d, o + 8, FA_VSZ)
            open(path, "wb").write(d)
            print("%s: .reloc vsz %#x -> %#x" % (path, old, FA_VSZ))
            return
    sys.exit("no .reloc section in %s" % path)


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "atf95/Release/FA.exe")