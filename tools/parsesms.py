#!/usr/bin/env python3
"""Parse FA.SMS — the shipped symbol map of Jane's Fighters Anthology.

Structure (little-endian, recovered from the binary):
  u32 count            (0xea9 = 3753; includes one phantom last entry)
  u32 zero             (observed 0 — likely type/reserved)
  (count-1) x { u32 VA, u32 end_off }   -- end_off = offset just past the
                                           symbol's NUL in the name pool
  u32 final VA                          -- last symbol, name = pool tail
  name pool: consecutive NUL-terminated strings; name _i spans
             pool[end_off[i-1] : end_off[i]], first name starts at 0.

Usage: parsesms.py <FA.SMS> [--coverage]
"""
import struct
import sys


def parse_sms(path):
    data = open(path, "rb").read()
    count, zero = struct.unpack_from("<II", data, 0)
    syms = []
    o = 8
    prev_end = 0
    for i in range(count - 1):
        va, end_off = struct.unpack_from("<II", data, o)
        o += 8
        syms.append((va, prev_end, end_off))
        prev_end = end_off
    final_va, = struct.unpack_from("<I", data, o)
    pool = data[o + 4:]
    names = []
    for va, s, e in syms:
        names.append((va, pool[s:e].rstrip(b"\0").decode("latin-1")))
    names.append((final_va, pool[prev_end:].rstrip(b"\0").decode("latin-1")))
    return names


def coverage(names):
    # FA.EXE: image base 0x400000, .text 0x401000..0x4e4eec, .rdata 0x4e5000,
    # .data 0x4e7000..0x589d98
    secs = {"text": (0x401000, 0x4e4eec), "rdata": (0x4e5000, 0x4e6452),
            "data": (0x4e7000, 0x589d98)}
    per = {k: [] for k in secs}
    for va, name in names:
        for s, (lo, hi) in secs.items():
            if lo <= va <= hi:
                per[s].append(va)
    for s, (lo, hi) in secs.items():
        v = sorted(per[s])
        span = hi - lo
        named = sum(1 for _ in v)
        print("%-6s: %5d symbols, span 0x%x" % (s, named, span))
    print("total: %d" % len(names))


def main():
    names = parse_sms(sys.argv[1])
    if "--coverage" in sys.argv:
        coverage(names)
    for va, name in names[:20]:
        print("0x%x  %s" % (va, name))


if __name__ == "__main__":
    main()