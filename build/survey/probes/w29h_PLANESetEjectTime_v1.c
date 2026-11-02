// _PLANESetEjectTime@4 @ 0x9b700 (80 B) — v1
// thm = _curThingType+0xba (a1 moffs + a8 test al => 32-bit load, low-byte test)
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
            w29h_ejtm = w29h_Rand(12) + w29h_curT + 4;
    } else
        w29h_ejtm = 0x7fff;
}