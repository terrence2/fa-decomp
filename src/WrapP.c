// @WrapP@4 @ rva 481264 (0x757f0, 48 B) — patch-hybrid.  Large-span note:
//   same shape as WrapHB with constant 0x5a00 — the patch replaces 42
//   bytes from offset 1 with FA's 47-B remainder (FA keeps *p in edx with
//   the lea-into-eax over-gate, dual `81 c2` add edx acc-forms on the wrap
//   path, `2d`/`05` sub/add mirror per path, mov al,1 placement per FA,
//   32 c0 c3 ret-0 and the 8d 64 24 00 pad); CL's reg-plan (eax park, edx
//   compute, 05 acc-forms, no pad) never matched across probes.  Span
//   replace judged EXACT.
//   Probe build/survey/probes/p_w23_WrapP_patch.obj EXACT (w23_r5.json;
//   ladder w23_WrapP_v1).
//   Maps (swap.json verbatim): [].
//   Patch: "1,42,118d8200a6ffff85c07e0a2d005a00008901b001c381c2005a0000790b81c2005a0000b0018911c332c0c38d642400".
extern long *wrapPPtr;  /* unused; arg arrives in ecx */

char __fastcall WrapP_q(long *p)
{
    long v = *p;
    long r = v - 0x5a00;
    if (r > 0) {
        *p = r - 0x5a00;
        return 1;
    }
    r = v + 0x5a00;
    if (r < 0) {
        v = r + 0x5a00;
        *p = v;
        return 1;
    }
    return 0;
}