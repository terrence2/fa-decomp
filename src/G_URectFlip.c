// _G_URectFlip@16 @ rva 0x967a0 (616352, 44 B code + 5 B 05 pad) — stdcall
//   wrapper: G_URect(a, *(int*)((char*)cb+6) - d - b, c, d) with operand
//   order (m-d)-b; FA reserves ebx for m (push ebx prologue, FPO cbRegs=1)
//   across the push interleave.
// EXACT as plain C (survey tier-1 probe v1): same PutCurObj
// inline-subscript-into-call-argument lever as the G_CircleFlip twin; CL
// reserves ebx for the m expression on its own once the subscript is
// inline. v2 (m in a named local) scheduled differently. Operand order
// (m-d)-b is the source-wording tell.
//
// probes: build/survey/probes/t1_flipu_v1.c (EXACT), t1_flipu_v2.c (no) —
//   run: python3 build/survey/hybrid_probe.py build/survey/probes/tier1_b1.json
//
// maps VERBATIM plus one NEW map (probe extern is the call shim):
//   "_G_URectQ=_G_URect@16"
extern char* cb;                        /* _cb (identity) */
extern void __stdcall G_URectQ(int a, int b, int c, int d);
                                        /* map _G_URectQ=_G_URect@16 */

void __stdcall G_URectFlip_q(int a, int b, int c, int d)
{
    G_URectQ(a, *(int *)((char *)cb + 6) - d - b, c, d);
}