// _PLANESetEjectTime@4 @ 0x9b700 — v5: 16-bit staged adds in the Rand path
extern unsigned long w29h_thm;     /* _curThingType+0xba */
extern unsigned short w29h_curT;   /* _currentT */
extern unsigned short w29h_ejtm;   /* _curThing+0x23c */
extern long __fastcall w29h_Rand(int n);   /* @Rand@4 */

void __stdcall PLANESetEjectTime(unsigned char u)
{
    if (w29h_thm & 0x10) {
        if (u)
            w29h_ejtm = w29h_curT;
        else {
            unsigned short t = w29h_Rand(12);
            t = t + w29h_curT;
            t = t + 4;
            w29h_ejtm = t;
        }
    } else
        w29h_ejtm = 0x7fff;
}