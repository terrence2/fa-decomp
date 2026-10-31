#!/usr/bin/env python3
"""Gate 1: byte-identity gate for built FA.exe vs the original.

Usage: python3 tools/gate.py [built-exe]   (default atf95/Release/FA.exe)

PASS  = byte-identical to FA/FA.EXE (sha256 match).
FAIL  = sha256 differs: report every differing region localized to the
        enclosing section + nearest enclosing/preceding symbol window
        from build/layout.json, so a diff is immediately actionable.
"""
import hashlib
import json
import sys

FA_EXE = "FA/FA.EXE"
LAYOUT = "build/layout.json"
IMAGE_BASE = 0x400000
CONTEXT = 16          # bytes of hex context printed around each region
MERGE_GAP = 16        # diff bytes within this gap merge into one region
MAX_REGIONS = 32


def sha256(path):
    return hashlib.sha256(open(path, "rb").read()).hexdigest()


def load_layout():
    try:
        with open(LAYOUT) as f:
            return json.load(f)
    except OSError:
        return None


def build_windows(layout):
    """Sorted list of (start_va, end_va, label) windows covering
    .text/.data chunks plus the linker-owned sections, so each byte lands
    in exactly one window (chunk extents tile their section)."""
    wins = []
    for key in ("text_chunks", "data_chunks"):
        for c in layout.get(key, []):
            sz = c.get("size", c.get("size_full", 0))
            nm = c.get("name")
            label = nm if nm else "<gap:%s+%x>" % (key[:4], c["rva"])
            wins.append((c["va"], c["va"] + max(sz, 1), label))
    for s in layout.get("secs", []):
        if s["name"] in (".idata", ".rsrc", ".reloc"):
            va = IMAGE_BASE + s["va"]
            wins.append((va, va + s["vsz"], s["name"]))
    wins.sort()
    return wins


def windows_for(wins, va):
    """(enclosing label, hint) for va; when not enclosed, the hint names the
    previous window and the next one's address."""
    label, where = wins[0][2], wins[0][2]
    for w0, w1, lab in wins:
        if va < w0:
            return label, "%s .. next window %s starts at %#x" % (where, lab, w0)
        label = lab
        where = lab
        if va < w1:
            return label, where
    return label, where


def regions(a, b):
    """Maximal diff regions (start, end), gaps < MERGE_GAP merged."""
    out = []
    i, n = 0, min(len(a), len(b))
    while i < n:
        if a[i] != b[i]:
            j = i
            while j < n and a[j] != b[j]:
                j += 1
            if out and i - out[-1][1] < MERGE_GAP:
                out[-1] = (out[-1][0], j)
            else:
                out.append((i, j))
            i = j
        else:
            i += 1
    return out


def off_local(off, layout, wins):
    """File offset -> ('section +delta (rva)', symbol window label) or (None, None)."""
    if not layout:
        return None, None
    for s in layout["secs"]:
        rptr, rsz = s.get("rawptr", 0), s.get("rawsz", 0)
        if rptr <= off < rptr + rsz:
            rva = off - rptr + s["va"]
            va = IMAGE_BASE + rva
            label, where = windows_for(wins, va) if wins else (None, None)
            return ("%s +0x%x (rva %#x)" % (s["name"], rva - s["va"], rva), where)
    return None, None


def main():
    built = sys.argv[1] if len(sys.argv) > 1 else "atf95/Release/FA.exe"
    sha_b, sha_f = sha256(built), sha256(FA_EXE)
    if sha_b == sha_f:
        print("GATE 1 PASS\n  %s\n  == %s" % (sha_b, FA_EXE))
        return 0
    a = open(built, "rb").read()
    b = open(FA_EXE, "rb").read()
    print("GATE 1 FAIL\n  built:    %s\n  original: %s" % (sha_b, sha_f))
    if len(a) != len(b):
        print("  LENGTH differs: built %d (0x%x) vs original %d (0x%x)" %
              (len(a), len(a), len(b), len(b)))
    layout = load_layout()
    wins = build_windows(layout) if layout else []
    if not wins:
        print("  (no %s — run tools/peref.py first for symbol localization)" % LAYOUT)
    regs = regions(a, b)
    print("  %d differing region(s), %d byte(s) total" %
          (len(regs), sum(e - s for s, e in regs)))
    for s, e in regs[:MAX_REGIONS]:
        loc, where = off_local(s, layout, wins)
        print("  0x%06x..0x%06x (%d B) %s | %s" %
              (s, e, e - s, loc or "??", where or ""))
        print("    built: %s" % a[s:e][:CONTEXT].hex())
        print("    FA:    %s" % b[s:e][:CONTEXT].hex())
    if len(regs) > MAX_REGIONS:
        print("  ... %d more region(s)" % (len(regs) - MAX_REGIONS))
    return 1


if __name__ == "__main__":
    sys.exit(main())