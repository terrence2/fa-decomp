/* @ShellClickSound@8 @ 0x8b190 — v1: sbb-select via direct ternary on constants */
extern unsigned short w28b_scr;      /* -> _curScreen */
extern unsigned short w28b_tcmp;     /* -> _timeCompression */
extern char w28b_click[];            /* -> _checkRightButton+0x464 */
extern char __stdcall w28b_SNM(char *file, short v2, short freq);              /* -> ?SoundNoMixer@@YGFPADFF@Z */
extern char __stdcall w28b_SS(char *file, unsigned char v2, unsigned char v3, unsigned char v4);  /* -> ?SingleSound@@YGFPADFEF@Z */

void __fastcall w28b_scs_f(long a, unsigned char b)
{
    short freq;
    if (w28b_scr == 0x10 && w28b_tcmp == 0x7fff) {
        freq = (short)(a / 4 - 80);
        w28b_SNM(w28b_click, (short)(255 + ((b & 0xff) < 1 ? -55 : 0)), freq);
    } else {
        w28b_SS(w28b_click, 0xff, 0xff, 0);
    }
}
