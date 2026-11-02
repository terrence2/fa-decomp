#!/usr/bin/env python3
"""Generate the wave-26 batch-C probe config (decimals from layout.json).

Each entry: rva pulled from the text_chunks name lookup (never hand-converted),
obj/src in build/survey/probes/.

Usage: python3 build/survey/probes/w26c_gen.py <variant> [rva-hex ...]
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__)))))
os.chdir(REPO)
L = json.load(open("build/layout.json"))


def rva_of(h):
    n = int(h, 16)
    for c in L["text_chunks"]:
        if c["rva"] == n:
            return c["rva"]
    raise SystemExit("no chunk rva %s in layout.json" % h)


NAME_BY_RVA = {}
for c in L["text_chunks"]:
    NAME_BY_RVA.setdefault(c["rva"], []).append(c["name"])


def base(h):
    """w26c_<file-ish> tag from the chunk's own name."""
    nm = (NAME_BY_RVA.get(int(h, 16)) or ["?"])[0]
    return nm


SUFFIXES = ["_v1", "_v2", "_v3", "_v4", "_v5", "_v6", "_v7"]


def main():
    argv = sys.argv[1:]
    if not argv:
        raise SystemExit("need variant")
    variant = argv[0]
    rs = argv[1:]
    es = []
    for h in rs:
        n = int(h, 16)
        rva = rva_of(h)
        for c in L["text_chunks"]:
            if c["rva"] == n:
                nm = c["name"]
                break
        else:
            raise SystemExit("no chunk rva %s in layout.json" % h)
        # file-friendly tag (readable, from the chunk table below)
        TAGS = {0x00a8a0: "HUDBrightness", 0x014240: "GetContactPositions",
                0x017c60: "PotRudder", 0x035760: "SoundName",
                0x04b840: "SER_ExNamesTimeout", 0x04c1f0: "SER_Shutdown1",
                0x05ec00: "GRPControl", 0x064340: "CTEval_tgtfacing",
                0x064400: "CTEval_htotgt", 0x064450: "CTEval_ptotgt",
                0x07f2a0: "UkraineCheckMaxPlanes", 0x07f840: "CampaignSave",
                0x087830: "TopCenterDialog", 0x08b4b0: "SAYMsg",
                0x08f8e0: "OBJAliasForMulti"}
        assert n in TAGS, "unmapped tag for rva %#x" % n
        tag = TAGS[n]
        srcs = [s for s in SUFFIXES
                if os.path.exists("build/survey/probes/w26c_%s%s.c"
                                  % (tag, s))] or [""]
        for suf in srcs:
            src = "build/survey/probes/w26c_%s%s.c" % (tag, suf)
            obj = "w26c_%s%s" % (tag, suf)
            maps = []
            patches = []
            # header maps live in the src's /* map ... */ comments
            txt = open(src).read()
            for line in txt.splitlines():
                if "/* map" in line:
                    m = line.split("/* map ", 1)[1].split(" */", 1)[0]
                    maps.append(m)
            t = txt.split("/* patch ", 1)
            if len(t) > 1:
                for part in t[1:]:
                    patches.append(part.split(" */", 1)[0].split("\n")[0])
            e = dict(rva=rva, obj=obj, src=src, maps=maps)
            if patches:
                e["patch"] = patches
            if variant.endswith("__keep"):
                e["flags"] = "/c /O2 /Gy /G5"
            es.append(e)
    json.dump(es, open("build/survey/probes/w26c_%s.json" % variant, "w"),
              indent=1)
    print("wrote build/survey/probes/w26c_%s.json (%d entries)" % (variant, len(es)))
    for e in es:
        print("  %-40s rva %d maps %d" % (e["obj"], e["rva"], len(e["maps"])))


if __name__ == "__main__":
    main()