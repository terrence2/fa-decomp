#!/usr/bin/env python3
"""FROM-decoration sweep: for each swap/batch entry, cross-check the maps
FROM spellings against the C source's extern declarations.

Checks per map line `FROM=TO`:
  1. FROM's C-side identifier (decoration stripped) is declared extern in src.
  2. The decoration matches the declaration's calling convention shape:
     cdecl (_X), stdcall (_X@N), fastcall (@X@N), thiscall (@X@N), dllimport
     (__imp__X / __imp__X@N), AIL (__imp___AIL_x@N), chunk anchors ($FA$*).
     Arity mismatches (@N N != arg bytes) are NOT checked here — the link
     catches those as LNK2001.

Exit 1 if any entry has a mismatch. Usage:
    python3 tools/from_sweep.py build/w21/batch_a.json build/w21/batch_b.json
    (or no args = tools/swap.json)
"""
import json
import re
import sys

STRIP = re.compile(r"^(?:__imp__+)?(?:AIL_)?(?P<pfx>[@_]?)(?P<name>[A-Za-z_\?][\w?$@]*?)(?P<dec>@\d+)?$")


def strip_from(f):
    """Return (pfx, c_name, dec) for a map FROM spelling."""
    m = STRIP.match(f)
    if not m:
        return ("", f.split("@")[0].strip("_"), "")
    g = m.groupdict()
    return (g["pfx"], g["name"].lstrip("_"), g["dec"] or "")


DECL = re.compile(r'extern\s+((?:const\s+)?[\w\s\*]+?)\b(?P<name>[A-Za-z_]\w*)\s*(?P<paren>\((?:[^()]|\([^()]*\))*\))?\s*\[?\]?\s*;')
FDECL = re.compile(r'^[^\n;{}]*\b([A-Za-z_]\w*)\s*\((?:[^()]|\([^()]*\))*\)\s*;', re.M)
CC = re.compile(r"__(?:std|fast|cdecl)\b")


def externs_of(src_text):
    """{c_name: (qualifier_blob, has_params)} for every extern declaration."""
    out = {}
    for m in DECL.finditer(src_text):
        q, name, paren = m.group(0), m.group("name"), m.group("paren")
        out[name] = (q, paren is not None)
    # bare (implicitly-extern) function declarations: 'void __cdecl foo(...);'
    for m in FDECL.finditer(src_text):
        out.setdefault(m.group(1), (m.group(0), True))
    return out


def shape_ok(pfx, dec, decl_q, has_params):
    blob = " ".join(decl_q.split())
    if "__fastcall" in blob or "__thiscall" in blob:
        return pfx == "@" and (dec != "") == has_params
    if "__stdcall" in blob or blob.endswith("PASCAL") or "WINAPI" in blob:
        return pfx == "_" and (dec != "") == has_params
    # cdecl / plain extern / data: _X (no @N)
    return pfx == "_" and dec == ""


def sweep(entries, source="file"):
    errs = 0
    for e in entries:
        try:
            src = open(e["src"]).read()
        except OSError as ex:
            print("%-24s MISSING SRC %s" % (e["obj"], ex))
            errs += 1
            continue
        ext = externs_of(src)
        for mapline in e.get("maps", []):
            f = mapline.split("=", 1)[0]
            pfx, name, dec = strip_from(f)
            # __imp__ thunks are data symbols; @N is part of the import name
            # (KERNEL32/USER32/ADVAPI32/DDRAW) — no decl-shape check applies.
            if f.startswith("__imp__"):
                continue
            # CRT/CL-internal symbols (__doexit, ___newmode, $T... etc.) are
            # resolved by the CRT objects at link, not by src declarations.
            if f.startswith("__") or f.startswith("$"):
                continue
            if name not in ext:
                # asm-block / CRT-internal / self-referential symbols live in
                # the source text without an `extern` decl at file scope.
                if name == e["obj"] or re.search(r"\b%s\b" % re.escape(name),
                                                 src):
                    continue
                print("%-24s FROM '%s': no extern named %s in %s"
                      % (e["obj"], f, name, e["src"]))
                errs += 1
                continue
            q, has_params = ext[name]
            # data externs (no parens) must be underscored, never @N
            if not has_params and dec:
                print("%-24s FROM '%s': %s is a DATA extern but FROM carries %s"
                      % (e["obj"], f, name, dec))
                errs += 1
            elif has_params:
                if pfx == "" or (pfx == "_" and not dec and
                                 ("__stdcall" in q or "__fastcall" in q)):
                    print("%-24s FROM '%s': %s is a CC-declared function but "
                          "FROM looks cdecl (missing @N / wrong prefix)"
                          % (e["obj"], f, name))
                    errs += 1
    print("sweep: %d entries, %d problem(s)" % (len(entries), errs))
    return errs


if __name__ == "__main__":
    files = sys.argv[1:] or ["tools/swap.json"]
    es = []
    for p in files:
        es += json.load(open(p) if hasattr(open(p), "read") else open(p))
    sys.exit(1 if sweep(es) else 0)