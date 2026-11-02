#!/usr/bin/env python3
"""Classify every swap.json entry by asm-escape reason, from the src file's
header comments (the reason text always lives there) + body shape.

Classes (census-ranked, see build/survey/asm_survey.md):
  thunk        6-byte import pass-through stubs (jmp [impXxx]) — trivial
  masm-enc     MASM/CL-unreachable FA encodings (moffs, sib, narrow forms)
  cc-shape     calling-convention structure (fastcall passthrough, xchg+jmp)
  reg-plan     CL register-allocation mismatch (parks/pins elsewhere)
  sched        scheduler / instruction-order diffs (a1-first, push-slot)
  seh-nlg      SEH/NLG + _emit short-jmp/MASM mnemonic walls
  const-fold   CL constant-folding / setcc / peephole rewrites
  gap-anchor   $FA$_t_ gap-chunk anchor mechanics
  dllimport    dllimport call-shape codegen diffs
  x87          x87 / control-word sequences
  elision      dis.py elision / literal-VA traps (fake difficulty)
  twin         twin-family copy
  plain        reached FA bytes as real C (incl. patch-hybrids)
  bare         asm without a recorded reason

Method: regex scoring over the FULL src text (headers repeat their reason
inside provenance quotes); priority-ordered so the most-specific tell wins.
Writes build/survey/reasons.json and prints a per-class summary.
"""
import json
import os
import re
import sys

ASM = re.compile(r"__asm|__declspec\(naked\)")

# (class, [regexes]) — first CLASS with a hit wins; order matters.
RULES = [
    ("thunk", [r"pass-through thunk", r"jmp\s+dword ptr \[\s*imp"]),
    ("elision", [r"elided by dis", r"ELIDED", r"cross-check raw FA",
                 r"dis\.py elision", r"literal.*VA.*reloc", r"literal FA-VA"]),
    ("twin", [r"\btwin\b"]),
    ("seh-nlg", [r"_emit\b", r"short[- ]?jmp", r"NLG", r"__except",
                 r"pusha", r"SEH", r"funclet"]),
    ("x87", [r"fstcw|fldcw|fistp|fstsw|fxam|fldz|control87|statusfp|clearfp"]),
    ("dllimport", [r"dllimport", r"__imp__\w+\s*=", r"ff 15 off the IAT"]),
    ("cc-shape", [r"thiscall|fastcall.*(passthrough|in (e|c)|-into)",
                  r"xchg|return address|jmp eax", r"cdecl.*ret|ret-skipping",
                  r"vtable|call \[eax|push 1 \+ call",
                  r"__int64 forms collapse|param never leaves"]),
    ("reg-plan", [r"register[- _]?(plan|alloc)|reg[- ]alloc|allocat",
                  r"parks|pinned? in|never leaves|role (re)?swap|swaps esi",
                  r"esi=ecx|edi=edx|in esi|in edi|in ebx|in ebp.*across",
                  r"kept in|rides EAX|mirror(ed)? (of|image)",
                  r"CL picks|reversed roles|opposite allocation|different regs"]),
    ("sched", [r"schedul", r"interleav", r"a1[- ]first|streams (the )?a1",
               r"hoist", r"between (the |its )?push|arg-push",
               r"load (d|_cb) (first|params first)", r"slot", r"order",
               r"pop esi BETWEEN", r"pushes? .*before"]),
    ("gap-anchor", [r"\$FA\$_t_.*anchor|gap chunk|unnamed chunk",
                    r"alias rule"]),
    ("const-fold", [r"constant[- ]fold|folds? the \d|CSE[- ]merge|folds? a",
                    r"setne|setle|sete (al|dl|cl) .*(FA|instead)|sbb/neg",
                    r"strength[- ]reduc|magic[- ]multiply|decomposes",
                    r"peephole|mem-(inc|dec)"]),
    ("masm-enc", [r"moffs|A-form|A2 (form|moffs)|sib[- ]?\d|MASM|spelling",
                  r"narrow|16-bit (reg )?forms|66-form|c6 05|c1-immediate",
                  r"cmp \[mem\]|byte-moffs|rep movsd|rep stosd|repne scasb",
                  r"imm32 needs OFFSET|a9 imm|24 fe|encoding"]),
    ("plain", [r"plain C|reached FA|probe .*exact|byte-exact|no patch needed"]),
]
# "probes exist in header" detector
PROBE = re.compile(r"probe[s]? \w|b\d\d_|w\d+\w*_|build/probe|runprobes")
GAME = re.compile(r"^(MISSION_|CT|CP_|CO|MSG_|MAP_|OBJ_|MM_|WNG_|AP_|WP_|"
                  r"PLANE_|NPC_|HUD|NET_|net_|SER_|ser_|G_|do_|Chunk_)\w*\.(c|cpp)$")


def classify(text):
    if not ASM.search(text):
        return "plain"
    for cls, rx in RULES:
        for r in rx:
            if re.search(r, text, re.I):
                return cls
    return "bare"


def main():
    es = json.load(open("tools/swap.json"))
    out = []
    for e in es:
        src_text = open(e["src"]).read()
        cls = classify(src_text)
        rva = e["rva"]
        out.append(dict(rva=rva, obj=e["obj"], src=e["src"], cls=cls,
                        patch=bool(e.get("patch")),
                        probes=bool(PROBE.search(src_text)),
                        game=bool(GAME.search(os.path.basename(e["src"])))))
    json.dump(out, open("build/survey/reasons.json", "w"), indent=1)
    from collections import Counter
    c = Counter(o["cls"] for o in out)
    print("per-class counts (all %d entries):" % len(out))
    for cls, n in c.most_common():
        print("  %-10s %3d" % (cls, n))
    g = Counter(o["cls"] for o in out if o["game"] and o["cls"] != "plain")
    print("\ngame-logic band asm (%d):" % sum(g.values()))
    for cls, n in g.most_common():
        print("  %-10s %3d" % (cls, n))
    print("\nnever-probed (bare/asm without probe refs):")
    for o in out:
        if o["cls"] != "plain" and not o["probes"]:
            print("  %-24s %s" % (o["obj"], o["cls"]))
    if len(sys.argv) > 1 and sys.argv[1] == "-v":
        for o in out:
            if o["cls"] not in ("plain", "thunk"):
                print("%-24s %-10s %s" % (o["obj"], o["cls"], o["src"]))


if __name__ == "__main__":
    main()