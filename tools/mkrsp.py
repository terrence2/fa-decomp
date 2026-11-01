#!/usr/bin/env python3
"""Emit the canonical Link-4.20 rsp for the stub+decompiled project.

Usage: python3 tools/mkrsp.py [--stubdir build/stubs] [--out build/m0/m.rsp]
       [--replace VA=Z:/work/.../obj]...

Reads <stubdir>/manifest.json for group order (VA order; a split chunk
produced by mkstub's SPLIT_AT becomes a singleton group) and renders:
  options line, .idata group objs, text groups, .data groups, .bss groups,
  the .rsrc obj (build/m0/FA.obj from CVTRES), then the trailing FA anchor
  object. --replace VA=file swaps the (singleton) stub group covering VA for
  a decompiled object, keeping its rsp position.
"""
import json
import os
import sys

STUBS = "build/stubs"
IDATA = "../build/idata"


def main():
    stubs, out = STUBS, "build/m0/m0link.rsp"
    repl = {}
    argv = sys.argv[1:]
    i = 0
    while i < len(argv):
        if argv[i] == "--stubdir":
            stubs = argv[i + 1]; i += 2
        elif argv[i] == "--out":
            out = argv[i + 1]; i += 2
        elif argv[i] == "--replace":
            va, fn = argv[i + 1].split("=", 1)
            repl[int(va, 0)] = fn; i += 2
        else:
            va, fn = argv[i].split("=", 1)
            repl[int(va, 0)] = fn; i += 1
    with open(os.path.join(stubs, "manifest.json")) as f:
        man = json.load(f)

    lines = ["/OUT:Release/FA.exe /MACHINE:IX86 /SUBSYSTEM:WINDOWS /NOLOGO "
             "/INCREMENTAL:NO /DEBUG /ENTRY:WinMainCRTStartup "
             "/EXPORT:T_HorizonProc /EXPORT:WRFogLayerUpdate"]
    lines += ["%s/idr%d.obj" % (IDATA, k) for k in range(5)]
    lines.append("%s/rdata.obj" % IDATA)
    for m in man:
        if m["kind"] != "textgroup":
            continue
        if m["va"] in repl:
            lines.append(repl[m["va"]])
        else:
            lines.append("../%s/%s" % (stubs, m["file"]))
    for m in man:
        if m["kind"] in ("datagroup", "bssgroup"):
            lines.append("../%s/%s" % (stubs, m["file"]))
    lines.append("../build/m0/FA.obj")
    with open(out, "w", newline="") as f:
        f.write("\r\n".join(lines) + "\r\n")
    print("wrote %s (%d objs, %d replaced)" % (out, len(lines) - 1, len(repl)))


if __name__ == "__main__":
    main()