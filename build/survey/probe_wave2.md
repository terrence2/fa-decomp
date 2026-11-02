# Survey probe wave 2 — the never-probed band: 2026-11-02 (59 re-C total, 15+ patch-hybrids)

Three parallel probe bands over the files the survey found never-probed (the
tier-0 wave covered 38 of them; this wave took the rest of the reachable
population). Same pipeline: probe → final src → targeted CL compile →
`swap._fit` → `from_sweep.py --objcheck` → full `swap.py link gate`.
Probe configs: `build/survey/probes/{tier1_a_r1..r6,tier1_b1,b2,tier1_re,w23_r1..r8}.json`.

## Conversions (59)

### Band A — never-probed leftovers (26 of 28 probed; 15 patch-hybrid)
socket_set_state, ConvertOldPreferredTargetId, lockerr_exit, APGetPark,
G_SetVShake, SetVShake, validate_packet, dlg_list_clear, FFMsgBanner,
CTEval_tgtattackingme, Ispunct, PROJEngineState, OnTheGround, jround_up,
Ui64toa = 15 patch-hybrids; GG_WaitRetrace (.cpp thiscall band), G_UPolygonFlip
(fastcall CC — cdecl decls emitted 83 c4 08 cleanups), InputCalibrate,
MTinitlocks (dllimport decl drops CL's extra indirection), COBv,
CTEval_canclimb, GetFakeKey, NetSetFactoryTCP, net_set_ready, RMShutdown,
BasicLinkSound = 11 plain C.
Keep-asm (2): per src headers.

### Band B (17 of 42 probed)
Wait, WaitKey, SetHShake, StringForLanguage, CPToggleHistory,
GG_ShutdownMode, GRPResponseSize, CTEval_tgt (identical-tail split: one return
value duplicated into two labels → both tails diverge, zero patches),
CTEval_maxalt, Alive, WrapHB + WrapP (whole-body synthesis, 42-B explicit
patch provenance), DialogDraw ×5, G_PolygonFlip, G_SPolygonFlip,
G_CopyDriverName, LFMult (`(__int64)a*b >> 16` inlines imul+shrd, no helper).

### Band C (16 of 41 probed)
verifyPacketCRC, G_CircleFlip, G_URectFlip (FROM `@N` decoration), DiskInit,
MAPSetSide, WNGWingmen, _mtterm (dllimport decl kills CL's ebx bookend),
IsBrentDLL, WNGInit, GRPInit, CTEval_alt, HeapInit (dllimport bookend
deletion ×2), CxxRestoreUnhEF, OBJTempAlias, PreferredProtectId,
ValidateExecute — 9 of them with patch directives.

## Merge-QA finds (this wave)

1. **fitobj renames**: `swap._fit` renames the CL obj's primary symbol to the
   FA chunk name — C names like `X_q` are fine at link; stale maps that
   mismatch the obj symbol leave LNK2001 externals that `--objcheck` flags.
2. **`__`-exemption trap**: a C identifier written with a leading underscore
   (e.g. `_crtheapX`) emits `__crtheapX`, which objcheck's internal-prefix
   exemption silently passes — LNK2001 only at link. The decl sweep catches it
   ("no extern named crtheapX"). Rule: fresh site symbols are C-side bare
   names; `__`-prefixed FROMs are reserved for CRT internals.
3. **Stale asm-escape provenance** must be dropped when a file converts; audit
   contract remains: keys `patch <offs>:` with offsets matching every
   directive, state word toolchain-diff for all live patches.
4. **Hex-rva labels from subagents are untrustworthy** again: two more wrong
   hex labels found (heap_term, G_SetHShake) — only entry decimals are
   authoritative.
5. Vestigial imp-maps swept (dllimport decls emit `__imp__X` directly): 6 more
   dropped; G_UPolygonFlip's three FROMs needed `@name@8` spellings.
6. GG_WaitRetrace is the wave-21 C++ thiscall band — the source belongs in
   `.cpp`, and the entry `src` field must follow.

## Remaining

- 11 band-A files unattempted (CallMemberFunction1, GRACos, CarefulDiv,
  do_start_interp, do_streamer_def, do_setlight, __abnormal_termination,
  WPGoalObjEvent, G_DrawYLR, NET_Addr2string, APObjOnShip) — next probe work.
- Keep-asm walls unchanged from tier-0: load-folds-to-test / 16-bit-slot
  forms / global re-materialization (now largely closed via 1–3-B patch
  hybrids instead of full asm keep).
## Gate-1 closeout (2026-11-02): linker addend semantics root-caused

The first full link after the merge failed GATE 1 (21 regions); every region
decomposed into five mechanics classes, confirmed by exact "2x" products
(built 0xa93c30 = 2x0x549e18):

1. **DIR32/REL32 addend model**: field = symVA + content (DIR32), symVA +
   content - addr_next (REL32). The content dword IS the addend. Patch
   payloads must carry ZERO dwords at site positions — FA's literal VA/rel
   gets added on top of the symbol and doubles (PROJEngineState,
   CTEval_maxalt x5, dlg_list_clear REL32). Fitobj's byte-verify EXEMPTS
   reloc'd dword sites, so a probe can pass EXACT while every addend is
   wrong; only the full link catches it.
2. **Site anchoring**: `,site:type:name` anchors the post-patch
   payload offset of the imm dword field — a1's imm is at payload+1,
   `8b 0d`'s at payload+2. Anchoring the opcode/modrm byte makes the addend
   bake read/write across the opcode span (PreferredProtectId: a1 -> 91
   01 00 00; OBJTempAlias: bake read "0d 00 00 00" and wrote 0x869).
3. **Crossed-load rewiring**: OBJTempAlias's a1 loaded nextObjId where FA
   loads ctNext (decl-order variants v5/v6 cannot move CL's choice), which
   also INVERTS the 3b c1 predicate. Fix: identical-length zero-shift
   patches at 0x0/0x5 drop CL's two dwords and re-add them under fresh map
   tokens (ctNext860A / nextObjId4A). This is the general cure for
   load-home inversions — and note byte-verify cannot see it (both wrong VA
   and inverted semantics hide inside exempt dwords).
4. **Import redirect idiom** (KEYECS, generalized): dllimport `__stdcall`
   decls emit decorated `__imp__X@N` refs that build a NEW appended IAT
   (+129 B .rdata, ff 15 <new-VA>). Map `__imp__X@N=__imp__X` (FA imports
   by undecorated names). Applied: MTinitlocks, MTterm, HeapInit x2,
   CxxRestoreUnhEF, ValidateExecute.
5. **CL 4.2 canonicalizes == evaluation order**: swapping the operands does
   NOT change the call stream. Statement-position temp
   (`c1 = A(p); return (char)(c1 == B(p));`) forces FA's call order but CL
   canonicalizes the compare to `cmp eax,reg` (3b c7 vs FA's 3b f8) —
   equality is direction-free, so the 1-B patch 0x1b,1,f8 closes it.

Fix list applied -> from_sweep --objcheck 0/0, audit 119 sites 0
unexplained, link clean, full gate pass (final counts in the commit).
