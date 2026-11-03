#!/usr/bin/env python3
"""Easiest-first candidate selector + progress tracker for bulk decompiling.

Usage:
  python3 tools/rank.py [--top N] [--exclude-seh] [--exclude-jt]
                          [--max-fixups N] [--json]
  python3 tools/rank.py --rva 0x87610        # dis + maps preview
  python3 tools/rank.py --update [--wave "note"]
                                   # rewrite tools/progress.json

Difficulty score over the not-yet-swapped text chunks (lower = easier;
weights calibrated so the 7 pilots order realistically):
  diff = size//4 + 2*ext_fx + 4*locals + 3*params
       + 25*unnamed + 10*mangled + 15*no_fpo + 35*seh + 8*jt
  ext_fx excludes in-chunk (self) targets -- CL $L labels handle those free.
  Known blind spot: scheduler-revision patch risk (LibRead) is invisible
  statically; the seh/jt/fixup columns let a human reorder cheaply.

progress.json is GENERATED: derived deterministically from swap.json; a
re-run with no change skips the write, so it never drifts and a manual edit
is overwritten by design.  Waves history is append-only via --wave.
"""
import json
import re
import struct
import subprocess
import sys
from datetime import date

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import sites  # noqa: E402

PROGRESS = __file__.rsplit("/", 1)[0] + "/progress.json"

SEH_PATS = [re.compile(b"\x64\x2b\x25\x00\x00\x00\x00")]  # unused; see below
SEH_BYTES = [b"\x64\xa1\x00\x00\x00\x00",      # mov eax,fs:[0]
             b"\x64\xa3\x00\x00\x00\x00",      # mov fs:[0],eax
             b"\x64\x8b\x25\x00\x00\x00\x00"]  # mov esp,fs:[0]
JT_SIBS = bytes(s for s in range(256)
                if (s >> 6) == 2 and (s & 7) in (4, 5) and (s & 0x38) != 0x38)


def chunk_ext_fx(rm, exe, chunk):
    """Exterior fixup count (in-chunk targets excluded)."""
    offs = [int(o) for o in rm["text"].get(str(chunk["va"]), [])]
    n = 0
    for o in offs:
        tgt, = struct.unpack_from("<I", exe, chunk["off"] + o)
        if not (chunk["va"] <= tgt < chunk["va"] + chunk["size"]):
            n += 1
    return n, len(offs)


def score(chunk, rm, exe):
    seh = jt = movzx = 0
    data = exe[chunk["off"]:chunk["off"] + chunk["size"]]
    for p in SEH_BYTES:
        if p in data:
            seh = 1
            break
    for i, b in enumerate(data[:-1]):
        if b == 0xff and data[i + 1] == 0x24 and i + 2 < len(data) and \
                data[i + 2] in JT_SIBS:
            jt = 1
    movzx = 1 if (b"\x0f\xb6" in data or b"\x0f\xb7" in data) else 0
    ext, tot = chunk_ext_fx(rm, exe, chunk)
    d = sites.fpo_decode(chunk) or {}
    named = chunk.get("name")
    diff = (chunk["size"] // 4
            + 2 * ext
            + 4 * d.get("cdwLocals", 0)
            + 3 * d.get("cdwParams", 0)
            + 25 * (0 if named else 1)
            + 10 * (1 if named and named.startswith("?") else 0)
            + 15 * (0 if d else 1)
            + 35 * (1 if (d and d["fHasSEH"]) or seh else 0)
            + 8 * jt)
    return dict(rva=chunk["rva"], name=named, size=chunk["size"],
                ext_fx=ext, fx=tot, locals=d.get("cdwLocals", 0),
                params=d.get("cdwParams", 0), fpo=bool(d), seh=seh, jt=jt,
                movzx=movzx, diff=diff)


def done_set(entries):
    """(rva, size) tuples covered by swap.json entries (spans tiled)."""
    L = sites.load_layout()
    done = set()
    for e in entries:
        rva = int(e["rva"], 0) if isinstance(e["rva"], str) else e["rva"]
        if e.get("span"):
            sp = int(e["span"], 0) if isinstance(e["span"], str) else e["span"]
            cs = [c for c in L["text_chunks"] if rva <= c["rva"] < rva + sp]
            for c in cs:
                done.add((c["rva"], c["size"]))
        else:
            c = next(c for c in L["text_chunks"] if c["rva"] == rva)
            done.add((c["rva"], c["size"]))
    return done, L


def cmd_list(args):
    top = 20
    excl_seh = excl_jt = False
    max_fx = None
    as_json = False
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--top":
            top = int(args[i + 1]); i += 2
        elif a == "--max-fixups":
            max_fx = int(args[i + 1], 0); i += 2
        elif a == "--exclude-seh":
            excl_seh = True; i += 1
        elif a == "--exclude-jt":
            excl_jt = True; i += 1
        elif a == "--json":
            as_json = True; i += 1
        else:
            raise SystemExit("unknown flag %s" % a)
    L = sites.load_layout()
    rm = sites.load_reloc_map()
    exe = sites.load_exe()
    entries = json.loads("\n".join(l for l in open(
        __file__.rsplit("/", 1)[0] + "/swap.json").read().splitlines()
        if not l.lstrip().startswith("//")))
    done, _ = done_set(entries)
    rows = [score(c, rm, exe) for c in L["text_chunks"]]
    cands = [r for r in rows if (r["rva"], r["size"]) not in done]
    if excl_seh:
        cands = [r for r in cands if not r["seh"]]
    if excl_jt:
        cands = [r for r in cands if not r["jt"]]
    if max_fx is not None:
        cands = [r for r in cands if r["fx"] <= max_fx]
    cands.sort(key=lambda r: (r["diff"], r["rva"]))
    if as_json:
        print(json.dumps(cands[:top], indent=1))
        return
    print("%-9s %-28s %6s %5s %5s %5s %3s %3s %6s"
          % ("rva", "name", "size", "extfx", "loc", "prm", "SEH", "JT",
             "diff"))
    for r in cands[:top]:
        print("%#09x %-28s %6d %5d %5d %5d %3d %3d %6d"
              % (r["rva"], (r["name"] or "")[:28], r["size"], r["ext_fx"],
                 r["locals"], r["params"], r["seh"], r["jt"], r["diff"]))
    print("== %d candidates un-done of %d chunks (showing %d)"
          % (len(cands), len(rows), min(top, len(cands))))


def cmd_preview(args):
    rva = int(args[0], 0)
    subprocess.run([sys.executable, __file__.rsplit("/", 1)[0] + "/dis.py",
                    "%#x" % rva], check=False)
    subprocess.run([sys.executable, __file__.rsplit("/", 1)[0] + "/mapgen.py",
                    "%#x" % rva], check=False)


def cmd_update(args):
    note = None
    if "--wave" in args:
        j = args.index("--wave")
        note = args[j + 1]
        del args[j:j + 2]
    entries = json.loads("\n".join(l for l in open(
        __file__.rsplit("/", 1)[0] + "/swap.json").read().splitlines()
        if not l.lstrip().startswith("//")))
    done, L = done_set(entries)
    try:
        old = json.load(open(PROGRESS))
    except Exception:
        old = None
    # copy, not alias: appending to old["waves"] in place would make
    # old == prog true after "generated" is restored and skip the write
    waves = list(old["waves"]) if old else []
    today = date.today().isoformat()
    cur_rvas = sorted("%#x" % r for r, _ in done)
    prev = set()
    for w in waves:
        prev.update(w["rvas"])
    if note is not None:
        new = [r for r in cur_rvas if r not in prev]
        waves.append({"date": today, "note": note, "rvas": new})
    bytes_done = sum(sz for _, sz in done)
    btotal = sum(c["size"] for c in L["text_chunks"])
    prog = {"functions_total": len(L["text_chunks"]), "done": len(done),
            "chunks_done": len(done), "bytes_done": bytes_done,
            "bytes_total": btotal,
            "bytes_pct": round(100.0 * bytes_done / btotal, 2),
            "waves": waves}
    if old:
        prog.pop("generated", None)
        if old == prog and not note:
            return  # unchanged: skip write (determinism invariant)
        prog["generated"] = old.get("generated", today)
    else:
        prog["generated"] = today
    if (not old or old != prog):
        w = json.dumps(prog, indent=1)
        print(w[:400])
        open(PROGRESS, "w").write(w + "\n")
        print("wrote", PROGRESS)


def main():
    args = sys.argv[1:]
    if not args or args[0].startswith("--top") or args[0] == "--json" or \
            args[0].startswith("--max") or args[0].startswith("--exclude"):
        cmd_list(args)
    elif args[0] == "--rva":
        cmd_preview(args[1:])
    elif args[0] == "--update":
        cmd_update(args[1:])
    else:
        cmd_list(args)


if __name__ == "__main__":
    main()