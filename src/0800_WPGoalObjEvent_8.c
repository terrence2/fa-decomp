// _WPGoalObjEvent@8 @ rva 0x97670 (620144) — 51 B code + 13 B (8d9b/8da424)
// pad. Pure CL C — EXACT fit, no patches. Probes w1..w5 (probes/).
//
// Lever (w5, decisive): `wpFlag &= ~(uchar)thingType` on the mapped extern
// directly makes CL do mov al,[wpFlag]/and al,bl/mov [wpFlag],al (a0/22c3/a2,
// 57 B). Staging the destination through a pointer local FIRST
// (`unsigned char *pf = &wpFlag;`) gets CL's RMW fold to emit
// `and byte [wpFlag],bl` (20 1d) — then pf never materializes and the
// byte-for-byte FA shape falls out, including the 16-bit slot loads
// (mov bx,[esp+0xc] / cmp ax,[esp+8]) the MaybeCallEventProc wall called
// unreachable: they arrive free from the word-typed params.
//
// Maps (unchanged from swap.json): _wpTgtSrc=_curThing+0xe8,
// _wpFlag=_curThing+0xec. Identity anchors: @WPDoingWaypoints@0 (fastcall,
// no args), _WPTarget@4 (stdcall ret-4 — cleans its arg so [esp+8] at the
// cmp is still p1). thingType stays cached in ebx across both calls.
//
// Compile: one CL /c /O2 /Gy /G5 shot; fit: fitobj <obj> 620144
//   --map '_wpTgtSrc=_curThing+0xe8' --map '_wpFlag=_curThing+0xec'
extern long wpTgtSrc;                   /* value dword at _curThing+0xe8 */
extern unsigned char wpFlag;            /* byte at _curThing+0xec */
extern char __fastcall WPDoingWaypoints(void);
extern unsigned short __stdcall WPTarget(long tgt);

void __stdcall WPGoalObjEvent(unsigned short wpId, unsigned short thingType)
{
    unsigned char *pf = &wpFlag;
    if (thingType != 0x10 && WPDoingWaypoints() &&
        WPTarget(wpTgtSrc) == wpId)
        *pf &= (unsigned char)~thingType;
}