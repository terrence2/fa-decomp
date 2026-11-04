// @LFMult@8 @ rva 797096 (0xc29a8, 12 B) — plain C.  Decisive lever: `__int64
//   a * b >> 16` DOES inline under CL 10.20.6166 (imul + shrd), unlike the
//   __allmul/__alldiv helper calls LFDiv/PAToF24 hit — and the OPERAND ORDER
//   steers which factor CL materializes into eax: v1's `(__int64)b * a` gave
//   mov eax,edx / imul ecx, FA wants mov eax,ecx / imul edx, so `a` must be
//   the first factor.  No patch; FA's 12-B chunk has no pad to reproduce.
//   Probe build/survey/probes/p_w23_LFMult_v2.obj EXACT (w23_r3.json;
//   ladder w23_LFMult_v1 + LFMult_patch attempt superseded).
//   Maps (swap.json verbatim): [].
extern int __fastcall LFMult_q(int a, int b);

int __fastcall LFMult_q2(int a, int b)
{
    return (int)(((__int64)a * b) >> 16);
}