#!/usr/bin/env python3
"""Gate 2: per-function slice comparison of a candidate FA.exe against the
original (reccmp-style), driven by build/layout.json chunk extents.

Usage:
  python3 tools/compare.py [built-exe]      # default atf95/Release/FA.exe
  python3 tools/compare.py A B              # compare any two exes
  python3 tools/compare.py --json out.json [built]

For .text chunks: match% = byte-equal fraction per chunk (function-sized).
For .data chunks: identical/divergent, with first-diff offset.
Summary per status; with --verbose list every non-identical function.
"""
import json
import sys

FA_EXE = "FA/FA.EXE"
LAYOUT = "build/layout.json"
IMAGE_BASE = 0x400000


def load(path):
    return open(path, "rb").read()


def rva_to_off(buf, layout, rva):
    for s in layout["secs"]:
        rptr, rsz = s.get("rawptr", 0), s.get("rawsz", 0)
        va = s["va"]
        if va <= rva < va + max(rsz, s.get("vsz", 0)):
            o = rptr + (rva - va)
            if o < len(buf):
                return o
    return None


def main():
    argv = sys.argv[1:]
    json_path = None
    if "--json" in argv:
        i = argv.index("--json")
        json_path = argv[i + 1]
        del argv[i:i + 2]
    built = argv[0] if argv else "atf95/Release/FA.exe"
    orig = argv[1] if len(argv) > 1 else FA_EXE

    with open(LAYOUT) as f:
        layout = json.load(f)
    a, b = load(built), load(orig)

    verbose = False
    rows = []
    for key in ("text_chunks", "data_chunks"):
        for c in layout.get(key, []):
            if key == "data_chunks":
                # compare only mapped file bytes; BSS chunks (size_file 0)
                # have no raw content and are skipped
                size = c.get("size_file", 0)
            else:
                size = c.get("size", 0)
            if size <= 0:
                continue
            rva = c["rva"]
            oa = rva_to_off(a, layout, rva)
            ob = rva_to_off(b, layout, rva)
            if oa is None or ob is None:
                rows.append(dict(kind=key, rva=rva, name=c.get("name"),
                                 size=size, match=0.0, status="off-map",
                                 first_diff=None))
                continue
            sa = a[oa:oa + size]
            sb = b[ob:ob + size]
            same = sum(x == y for x, y in zip(sa, sb))
            match = same / size
            fd = next((i for i, (x, y) in enumerate(zip(sa, sb)) if x != y), None)
            status = "identical" if sa == sb else "differ"
            rows.append(dict(kind=key, rva=rva, name=c.get("name"), size=size,
                             match=round(match, 4), status=status,
                             first_diff=rva + fd if fd is not None else None))

    txt = [r for r in rows if r["kind"] == "text_chunks"]
    dat = [r for r in rows if r["kind"] == "data_chunks"]
    ok_t = sum(1 for r in txt if r["status"] == "identical")
    ok_d = sum(1 for r in dat if r["status"] == "identical")
    pct_t = sum(r["match"] * r["size"] for r in txt)
    tot_t = sum(r["size"] for r in txt)
    print("text: %d/%d chunks identical, %.2f%% of bytes" %
          (ok_t, len(txt), 100.0 * pct_t / tot_t if tot_t else 100.0))
    print("data: %d/%d chunks identical" % (ok_d, len(dat)))
    for r in sorted(txt, key=lambda r: r["match"])[:20]:
        if r["status"] == "identical":
            break
        fd = " firstdiff=%#x" % r["first_diff"] if r["first_diff"] is not None else ""
        print("  text %#x %-32s %.1f%%%s" %
              (r["rva"], (r["name"] or "<gap>")[:32], 100 * r["match"], fd))
    for r in dat:
        if r["status"] != "identical":
            fd = " firstdiff=%#x" % r["first_diff"] if r["first_diff"] is not None else ""
            print("  data %#x %-32s %.1f%%%s" %
                  (r["rva"], (r["name"] or "<gap>")[:32], 100 * r["match"], fd))
    if json_path:
        with open(json_path, "w") as f:
            json.dump(rows, f, indent=1)
    bad = len(rows) - ok_t - ok_d
    return 0 if bad == 0 else 1


if __name__ == "__main__":
    sys.exit(main())