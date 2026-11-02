// @SetHShake@8 @ rva 75712 (0x127c0, 48 B) — patch-hybrid.  The plain-C body
//   (3 early-return gates + fastcall tail call) reproduces 45/48 bytes; the
//   last wall is FA's direct mem-test of mainV[0x1a]: FA `f6 05 <imm>,01`
//   (7 B, test byte [moffs],1) vs CL 0xC-0x12 `a0 <imm> a8 01` (al-load +
//   test al — CL 10.20.6166 materializes byte loads before tests).  Patch
//   swaps the 7-byte al-load pair for FA's mem-test with a fresh site symbol
//   (patch sites must not reuse the obj's own content addends).
//   Probe build/survey/probes/p_w23_SetHShake_patch.obj EXACT (w23_r2.json).
//   Maps (swap.json verbatim + patch site): mainV2=_mainV+0x1a.
//   Patch: "12,7,f6050000000001,2:6:mainV2".
extern char mainV[];
extern unsigned short playerId;
extern long gamePrefs;
extern void __fastcall G_SetHShake(long a, long b);

void __fastcall SetHShake_q(long a, long b)
{
    if ((gamePrefs & 0x8000000) == 0)
        return;
    if ((mainV[0x1a] & 1) == 0)
        return;
    if (playerId == 0)
        return;
    if (playerId != *(unsigned short *)(mainV + 0x1c))
        return;
    G_SetHShake(a, b);
}