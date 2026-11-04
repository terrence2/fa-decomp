// _PLANESetEjectTime@4 @ 0x9b700 (636672, 80 B: 76 code + 8d642400 census
// tail) — EXACT with 4 maps + 1 patch.
//
// Fits: (1) thm must be a 32-bit scalar so CL emits a1 moffs + a8 10
// (unsigned short spelling gives f6 05 test-[mem],imm — the v2 regression);
// (2) u-path stores go through CL's 66 8b 0d / 66 89 0d modrm forms with
// curT in CX — the plain `ejtm = curT;` statement; staging `t` first
// (v3/v5) pushes CL onto the ax/moffs forms and shifts the u-path;
// (3) the Rand(12) path: CL holds the call result as a 32-bit int and
// fuses Rand+curT+4 into mov cx,[curT] + lea eax,[eax+ecx+4] for EVERY
// spelling tried (long-Rand v1, short-Rand v6, staged adds v5) while FA
// keeps the adds 16-bit in ax — closed by patch below.
//
// fitobj (EXACT):
// python3 tools/fitobj.py build/survey/probes/w29h_PLANESetEjectTime_v4.obj 0x9b700 \
//   --map "_w29h_thm=_curThingType+0xba" --map "_w29h_curT=_currentT" \
//   --map "_w29h_ejtm=_curThing+0x23c" --map "@w29h_Rand@4=@Rand@4" \
//   --patch "0x2c,11,6603050000000066050400,3:6:_w29h_curT" \
//   build/survey/probes/w29h_PLANESetEjectTime_v4_fit.obj
extern unsigned long w29h_thm;     /* _curThingType+0xba */
extern unsigned short w29h_curT;   /* _currentT */
extern unsigned short w29h_ejtm;   /* _curThing+0x23c */
extern long __fastcall w29h_Rand(int n);   /* @Rand@4 */

void __stdcall PLANESetEjectTime(unsigned char u)
{
    if (w29h_thm & 0x10) {
        if (u)
            w29h_ejtm = w29h_curT;
        else
            w29h_ejtm = (unsigned short)w29h_Rand(12) + w29h_curT + 4;
    } else
        w29h_ejtm = 0x7fff;
}