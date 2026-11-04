/* wave 31C: _MaybeExitToDOS@0 (FA rva 0x11df0, 0x60 B) v1 */
extern char w31cDin[];
extern unsigned char w31cAdc;
extern short __stdcall w31cDD(char *, long);      /* _DoDialogInfoBox@8 */
extern char __stdcall w31cPS(char *, long, long); /* ?PlaySeq@@YGDPADJJ@Z */
extern void __cdecl w31cWC(void);                 /* _WriteConfig */
extern void __cdecl w31cEE(long);                 /* _ErrorExit */

void w31cME(void)
{
    short r;
    unsigned char c;
    r = w31cDD(&w31cDin[8], 3);
    if (r == 1) {
        c = w31cAdc;
        if (c < 3) {
            w31cPS(&w31cDin[4], 0x280, 0x1e0);
            ++w31cAdc;
        } else {
            ++c;
            w31cAdc = c;
            if (c > 100) w31cAdc = 3;
        }
        w31cWC();
        w31cEE(0);
    }
}