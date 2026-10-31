#!/usr/bin/env python3
"""Emit 3 tiny unaligned .text objs (5, 7, 11 bytes) to probe link 4.20's
padding semantics: plain vs COMDAT sections."""
import sys, struct
sys.path.insert(0, "tools")
import coff

def emit(nm, size, comdat, fpo=False):
    code = bytes(range(0x50, 0x50 + size))
    flags = coff.S_TEXT_COMDAT if comdat else coff.S_TEXT_PLAIN
    obj = coff.build_stub_obj(code, flags, "_" + nm)
    path = "build/m0/%s.obj" % nm
    open(path, "wb").write(obj)
    return path

emit("tplain_a", 5, False)
emit("tplain_b", 7, False)
emit("tcomdat_a", 11, True)
print("emitted")
