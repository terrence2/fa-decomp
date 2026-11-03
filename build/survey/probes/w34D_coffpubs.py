#!/usr/bin/env python3
import struct, sys

def publics(path):
    d = open(path, 'rb').read()
    nsec, = struct.unpack_from('<H', d, 2)
    symptr, nsyms = struct.unpack_from('<II', d, 8)
    optlen, = struct.unpack_from('<H', d, 16)
    o = []
    i = 0
    while i < nsyms:
        base = symptr + i * 18
        name = d[base:base + 8]
        zero, off = struct.unpack_from('<HI', d, base + 8)
        if zero == 0:
            end = d.find(b'\x00', off)
            name = d[off:end]
        sec = struct.unpack_from('<h', d, base + 12)[0]
        typ = struct.unpack_from('<h', d, base + 14)[0]
        val = struct.unpack_from('<I', d, base + 16)[0]
        naux = d[base + 16]
        i += 1 + naux
        if sec > 0 and typ in (0, 0x20, 32):
            o.append((name.decode('latin1'), sec, val))
    return o

def main():
    path = sys.argv[1]
    for name, sec, val in publics(path):
        print(sec, hex(val), name)

main()