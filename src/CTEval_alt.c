// _CTEval_alt @ rva 0x646d0 (411344, 44 B code + 4 B pad) — (dword at
//   curThing+0x15 - T_Info(curId, curThing, curThing+0x11, 0, 0, 0)) >> 8.
//   FA asm: push esi/push 0/66 a1 <_curId> (16-BIT moffs load, garbage
//   upper eax)/8b 35 <curThing+0x15> (esi dword stream interleaved AFTER
//   the first push)/push 0/push 0/push <curThing+0x11>/push <curThing>/
//   push eax/e8 _T_Info@24/2b f0/c1 fe 08/8b c6/5e/c3.
//   Naked-asm escape: FA's 66 a1 16-bit curId load (mov eax, word[mem]
//   without zero-extension) is the CTEval twin-family moffs A-form, and
//   the 8b 35 esi load is interleaved into the push chain.
// patch-hybrid (survey tier-1, 1 region patch): plain C with a signed
//   short arg (66-a1 spelling) puts CL's curId load in the right place,
//   but CL emits 33 c0 zero-extension and hoists the esi load BEFORE the
//   push block, in the opposite order.
//   patch 0x3: replace CL[0x3,0x15) — 8b 35 <curThing+0x15> / 6a 00 /
//     6a 00 / 33 c0 / 66 a1 <_curId>, 18 B — with FA's 16 B order
//     66 a1 <_curId> / 8b 35 <curThing+0x15> / 6a 00 / 6a 00, DIR32
//     attached at sites 2/8 (-2 B net; the 0x11 addend baked in the
//     0x15 d32; later push/e8 relocs shift automatically).
//
// probes: build/survey/probes/t1_ctalt_v1.c (EXACT via patch), _v2/_v3.c
//   (no) — run: python3 tools/fitobj.py build/survey/probes/t1_ctalt_v1.obj
//   411344 --map '_T_InfoQ=_T_Info@24'
//   --patch '0x3,18,66a1000000008b35150000006a006a00,2:6:_curId,8:6:_curThing'
//
// maps VERBATIM plus NEW: "_T_InfoQ=_T_Info@24"
//   (curId/curThing resolve identity)
extern unsigned short curId;
extern char curThing[];
extern long __stdcall T_InfoQ(long a, long b, long c, long d, long e, long f);
                            /* map _T_InfoQ=_T_Info@24 */

long CTEval_alt_q(void)
{
    long d = *(long *)((char *)curThing + 0x15);
    return (d - T_InfoQ(curId, (long)curThing, (long)(curThing + 0x11),
                        0, 0, 0)) >> 8;
}