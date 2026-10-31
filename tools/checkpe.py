#!/usr/bin/env python3
"""Report PE header facts + SHA-256 for a PE32 file.

Usage: checkpe.py <file> [--expect-sha256 <hex>]
"""
import hashlib
import struct
import sys


def main():
    path = sys.argv[1]
    data = open(path, "rb").read()
    e_lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    assert data[e_lfanew:e_lfanew + 4] == b"PE\0\0", "not a PE"
    machine, nsec, ts, symptr, nsym, oh, chars = struct.unpack_from("<HHIIIHH", data, e_lfanew + 4)
    opt = e_lfanew + 4 + 20
    majlm, minlm = data[opt + 2], data[opt + 3]
    subsystem, = struct.unpack_from("<H", data, opt + 68)
    print("machine=0x%04x linker=%d.%02d subsystem=%d timestamp=0x%08x sections=%d"
          % (machine, majlm, minlm, subsystem, ts, nsec))
    print("size=%d sha256=%s" % (len(data), hashlib.sha256(data).hexdigest()))
    if "--expect-sha256" in sys.argv:
        expect = sys.argv[sys.argv.index("--expect-sha256") + 1]
        ok = hashlib.sha256(data).hexdigest() == expect
        print("MATCH=%s" % ("YES" if ok else "NO"))
        sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()