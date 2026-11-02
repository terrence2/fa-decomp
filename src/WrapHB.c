// @WrapHB@4 @ rva 481216 (0x757c0, 48 B) — patch-hybrid.  Large-span note:
//   the patch replaces 42 bytes from offset 1 with FA's 47-B remainder —
//   FA: *p load parked in EDX (`8b 11`) with the -0xb400 result lea'd into
//   eax (`8d 82 00 4c ff ff`), jle +0x0a to the wrap path; over path does
//   `2d 00 b4 00 00` sub-from-eax, store [ecx],eax, mov al,1, ret; wrap
//   path adds in EDX twice (`81 c2` add edx,0xb400 acc-form) keeping the
//   value in edx for the final store (89 11) with mov al,1 before it, then
//   `32 c0 c3` ret-0 and an `8d 64 24 00` pad.  CL (1 probe + ladder,
//   never matched across the axis) parks *p in eax (`8b 01`), computes in
//   edx, uses `05` acc-form adds on eax, orders mov al,1 BEFORE the store
//   in the over path, and emits no pad.  Plain-C semantics were correct;
//   the whole reg-plan is FA-synthesized by the span replace.
//   Probe build/survey/probes/p_w23_WrapHB_patch.obj EXACT (w23_r5.json;
//   ladder w23_WrapHB_v1).
//   Maps (swap.json verbatim): [].
//   Patch: "1,42,118d82004cffff85c07e0a2d00b400008901b001c381c200b40000790b81c200b40000b0018911c332c0c38d642400".
extern long *wrapHBPtr;  /* unused; arg arrives in ecx */

char __fastcall WrapHB_q(long *p)
{
    long v = *p;
    long r = v - 0xb400;
    if (r > 0) {
        *p = r - 0xb400;
        return 1;
    }
    r = v + 0xb400;
    if (r < 0) {
        v = r + 0xb400;
        *p = v;
        return 1;
    }
    return 0;
}