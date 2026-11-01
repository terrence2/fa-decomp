#!/usr/bin/env python3
"""Bisect which wave-2 swap entry flips the tail word at exe 0x131a09.

The FA image's linker-appended debug tail carries a 2-byte field at
0x131a09..0x131a0a (FA: 00 00). Wave-1 links matched FA there; the
current wave-2 link produces 1b b9. This driver rewrites tools/swap.json
to a subset, regenerates stubs + rsp + links (seed clock only -- the
tail carries no timestamps; both links of a swap.py run produce
identical tails), probes the bytes, and restores the original file.

The wave-1/pilot entries are always kept: a known-clean baseline.

Usage:
  python3 tools/bisect_tail.py backup            # snapshot current swap.json
  python3 tools/bisect_tail.py set <obj[,obj]>   # keep wave-1 + listed objs, link, probe
  python3 tools/bisect_tail.py probe             # probe the current FA.exe
  python3 tools/bisect_tail.py restore           # full swap.json back
  python3 tools/bisect_tail.py bisect            # binary-search the wave-2 names
"""
import json
import shutil
import subprocess
import sys

BACKUP = "build/bisect_tail_swap.json"
WORD_OFF = 0x131a09


def load_backup():
    txt = [ln for ln in open(BACKUP)
           if not ln.lstrip().startswith("//") and ln.strip()]
    return json.loads("\n".join(txt))


def swap_objs():
    return [e["obj"] for e in load_backup()]


def parse_swap(txt):
    txt = "\n".join(ln for ln in txt.splitlines()
                    if not ln.lstrip().startswith("//"))
    return json.loads(txt)


def wave2_names():
    """All objs beyond the committed wave-1 + pilot set (git HEAD)."""
    import subprocess as sp
    head = sp.run(["git", "show", "HEAD:tools/swap.json"],
                  capture_output=True, text=True).stdout
    head_objs = {e["obj"] for e in parse_swap(head)}
    return [o for o in swap_objs() if o not in head_objs]


def write_subset(names):
    wave2 = set(wave2_names())
    names = set(names)
    es = [e for e in load_backup()
          if e["obj"] not in wave2 or e["obj"] in names]
    body = "".join("  %s,\n" % json.dumps(e) for e in es)
    with open("tools/swap.json", "w") as f:
        f.write("[\n" + body[:-2] + "\n]\n")  # drop the trailing comma
    return len(es)


def link_and_probe():
    r = subprocess.run([sys.executable, "tools/swap.py", "link"],
                       capture_output=True, text=True)
    if r.returncode:
        sys.exit("link failed: " + r.stdout[-3000:] + r.stderr[-3000:])
    d = open("atf95/Release/FA.exe", "rb").read()
    return d[WORD_OFF:WORD_OFF + 2].hex()


def probe():
    return open("atf95/Release/FA.exe", "rb").read()[WORD_OFF
                                                    :WORD_OFF + 2].hex()


def bisect(names):
    write_subset([])
    base = link_and_probe()
    print("baseline (0 of %d): %s" % (len(names), base))
    if base != "0000":
        sys.exit("baseline not clean -- wave-1 entries or rsp regressed")
    lo = sorted(names)
    while len(lo) > 1:
        half = sorted(lo)[:len(lo) // 2]
        write_subset(half)
        w = link_and_probe()
        print("half[%s..%s] (%d): %s" % (lo[0], half[-1], len(half), w))
        if w == "0000":
            lo = sorted(lo)[len(half):]
        else:
            lo = half
    write_subset(lo)
    w = link_and_probe()
    print("SINGLE NAME %s -> word %s" % (lo[0], w))


if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else ""
    if cmd == "backup":
        shutil.copy("tools/swap.json", BACKUP)
        print("backed up %d entries" % len(load_backup()))
    elif cmd == "probe":
        print("tail word:", probe())
    elif cmd == "restore":
        shutil.copy(BACKUP, "tools/swap.json")
        print("restored %d entries" % len(load_backup()))
    elif cmd == "set":
        n = write_subset([x for x in sys.argv[2].split(",") if x.strip()])
        print("entries linked: %d, tail word: %s" % (n, link_and_probe()))
    elif cmd == "bisect":
        bisect(wave2_names())
    else:
        sys.exit(__doc__)