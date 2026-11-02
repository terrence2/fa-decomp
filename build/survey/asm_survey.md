# FA decomp: why 415 of 936 functions carry `__asm` — survey (2026-11-01)

Sources: per-file header comments (936 swap.json entries), tools/progress.json
(waves pilot-21), TODO.md, git wave logs, docs/PATCH-FORENSICS.md,
docs/MSVC_VERSION.md, tools/swap.json provenance. Machine-readable map:
`build/survey/reasons.json` (regenerate: `python3 build/survey/classify.py`, -v lists).

## Headline numbers (spot-checked)

| | count |
|---|---|
| entries with `__asm` (415 total; 397 `__declspec(naked)`) | all-or-nothing policy: **zero hybrids** — 313/415 have no C statement outside the block |
| import pass-through thunks (`jmp dword ptr [impX]`, 6 B) | **209** — trivial class, hides the real population |
| **non-thunk asm escapes** | **~206** |
| reached FA bytes as real C (incl. 11 patch-hybrids) | **521** |

## Ranked reason classes (206 non-thunk, from header reasons)

| # | class | files | recovery outlook |
|---|---|---|---|
| 1 | **MASM/CL-unreachable FA encodings** — moffs A-forms, sib spellings, `cmp [mem],imm`, narrow 8/16-bit ops, `c6 05` direct stores, rep blocks | 80 (census) / 23 (regex) | **Highest value**: many are 1–3 B deltas → patch-hybrid (11 existing proofs); rep blocks = intrinsic re-probe |
| 2 | Calling-convention shape (0-arg fastcall passthrough, thiscall-by-hand, `xchg`+`jmp eax`, vtable calls) | 26 | low — mostly structural; keep asm |
| 3 | **CL register-plan mismatch** (parks/pins/swaps, value never leaves a reg, ebx reserved across pushes) | 23–49 | medium — probes were ad hoc (2–4 variants); never swept with the systematic lever matrix |
| 4 | **Scheduler/instruction-order** (a1-first, store-between-pushes, interleave, load-order twins) | 18–32 | medium — some levers proven (CTInit slot, HUDReprintMessages stream); untapped re-probe |
| 5 | SEH/NLG + `_emit` short-jmp/MASM mnemonic walls (pusha 66-prefix, e9-vs-eb) | 14 | none; keep asm |
| 6 | Constant-fold/setcc/peephole rewrites (CL folds mem-inc/dec, setcc reg choice, CSE merge, or-word→byte) | 11 | medium — typing levers proven (char-vs-ulong, ushort width, volatile CSE); spellings unexplored |
| 7 | Gap-chunk `$FA$_t_` anchor mechanics | 11 | none; link plumbing, not C patterns |
| 8 | dis.py **elision false negatives** (instructions the disassembler omitted → "unsteerable" decided against incomplete bytes) | 5–11 | high, trivial — re-read with raw-byte cross-check (VDOInit/FFMsgBanner/HARDStoreWeight pattern) |
| 9 | dllimport call-shape codegen diffs | 9 | low |
| 10 | x87/control-word (fstcw 9b-placement, __ftol, fxam) | 6 | low |
| 11 | twin-family copies (SetVShake, GRPWingmen…) | 2–8 | free when family leader converts |
| — | bare headers, no reason recorded (early waves) | 5 | probe from scratch |

## Game-logic band (the implausibility question)

62 asm files in the MISSION_/CO_/CP_/CT_/MSG_/MAP_/OBJ_/MM_/WNG_/AP_/WP_/NPC_
band; **none is genuinely assembly-flavoured**. Reason mix: 38 MASM-encoding
class, 7 CC, 4 scheduler, 4 register-plan, 3 setcc-fold, 3 gap-anchor,
3 elision. Flagships:

- `MISSIONEnsureLegalName` (0x84a60) — in-place '.'/'^' deletion loop;
  failed 4 probes on the repne-scasb strlen + `i`-in-ebx register plan.
- `CTEval_*` set (canclimb, alt, maxalt, tgt*) — one-compare predicates
  escaping over setcc-result regs and 66-mem-compare order.
- `PutFakeKey/GetFakeKey/OBJTempAlias/OBJNextAliasForMulti` — mem inc/dec +
  moffs stores; CL folds what FA spelled out.
- `Clampit/Vertical/Alive/OnTheGround/MaxSpeed` — one-comparison clamps.
- `PopCurObj/PutCurObj` — rep-movs copy + sib spellings (PopCurObj only
  needed a 1-byte modrm patch → proof #9 that "hard" here means "byte delta").

## What the survey says to do (probe ladder)

1. **never-probed/bare first** (cheapest wins; see reasons.json list): G_HFlipBitmap,
   EnvHighest, PLANEUpdateJustLanded, HARDNumLoaded, SetScenarioEndTime,
   CTDo_exit, OBJStopAdding, G_StringWidth, IsZeroMan, FcloseLk + elision class
   (MaxSpeed, MISSIONSetCheating, AlmostHome, get_pkt_err_string, _line_overflow1, CDirDrawSurfaceUnlock).
2. **rep-block intrinsic re-probe**: __strcats, MISSIONEnsureLegalName
   (repne scasb → strlen), fread/fwrite fprintf wrappers.
3. **lever matrix** on reg-plan/top sched files: MISSIONEnsureLegalName,
   StringForLanguage, WrapHB, SER_RemoteQueueFull family, NPCSetStateTarget,
   COThrust, RotatedOffset, PutCurObj, InBounds3, verifyPacketCRC.
4. **patch-hybrid sweep** on the 80-file MASM-encoding class (1–3 B deltas).
5. **per-TU flag axis**: swap.json `flags` key, 0/936 users; ~20-set matrix
   (lrflags.py sets) per stuck file, CRT band first.
6. keep-asm (no further work): thunks (209), SEH/NLG/_emit (14), x87 (6),
   gap-anchor (11), CC-structural (most of 26), dllimport shape.

## Compiler-revision context

All diffs are `toolchain-diff`-classified: our CL 10.20.6166 (retail VC4.2)
vs FA's unknown 4.2 revision — scheduler/register/peephole deltas concentrated
under /G5. VC 4.2b patch toolset = the feasible follow-up (MSVC_VERSION.md);
winworldpc has 4.2 Enterprise/Professional disks only (same revision,
probably) — 4.2b may be lost to time. Everything else here must close via
source spells + patches.