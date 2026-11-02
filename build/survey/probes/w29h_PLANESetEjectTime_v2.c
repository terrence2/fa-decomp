// _PLANESetEjectTime@4 @ 0x9b700 — v2: thm as unsigned short (16-bit load guess)
extern unsigned short w29h_thm;    /* _curThingType+0xba */
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