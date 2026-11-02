/* ?AtFriendlyAP@@YGDXZ @ rva 0x7f670 (64 B) — stdcall char(void):
   if (!OnTheGround()) return 0;  else l = APNearest(_curThing,
   _curThing+0x11, &l, 0, 0) written into the local; return l < 0xa5000
   (cmp [esp],0xa5000 / setl dl / mov al,dl — the cmp is hidden in dis.py). */
extern char __stdcall w29e_otg(void);      /* =_OnTheGround@0 */
extern void __stdcall w29e_apn(char *a, char *b, long *c, long d, long e);
                                           /* =_APNearest@20 */
extern char w29e_ct[];                     /* =_curThing */

char __stdcall AtFriendlyAPW(void)
{
    long l;
    if (!w29e_otg())
        return 0;
    w29e_apn(w29e_ct, w29e_ct + 0x11, &l, 0, 0);
    return l < 0x000a5000;
}