// _G_CircleFlip@16 @ rva 0x96770 (616304, 43 B code + 8 B 8d64x2 pad) —
//   stdcall wrapper: G_Circle(a, *(int*)((char*)cb+6) - b - 1, c, d).
//   FA loads the d/c params first, pushes d, THEN loads _cb into edx
//   (8b 15) and keeps c/b as stack reloads.
//   G_CircleFlip twin family. Naked-asm escape.
// EXACT as plain C (survey tier-1 probe v1): the PutCurObj lever — inline
// the subscript into the call argument. v2 separated out a local m and CL
// scheduled the _cb load first (8b 0d) with the m-add from a stack read.
//
// probes: build/survey/probes/t1_flipc_v1.c (EXACT), t1_flipc_v2.c (no) —
//   run: python3 build/survey/hybrid_probe.py build/survey/probes/tier1_b1.json
//
// maps VERBATIM plus one NEW map (probe extern is the call shim):
//   "_G_CircleQ=_G_Circle@16"
extern char* cb;                        /* _cb (identity) */
extern void __stdcall G_CircleQ(int a, int b, int c, int d);
                                        /* map _G_CircleQ=_G_Circle@16 */

void __stdcall G_CircleFlip_q(int a, int b, int c, int d)
{
    G_CircleQ(a, *(int *)((char *)cb + 6) - b - 1, c, d);
}