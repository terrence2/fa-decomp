/* @ShellButtonSound@4 @ 0x8b140 (80B)
   FA: checks word[curScreen]==0x10 && word[timeCompression]==0x7fff; then
   signed div by 4 of the ecx param with cdq+and+add+sar (arg3 = short):
   8bc1 99 83e203 03c2 c1f802; sub AX,0x50 (66 2d 5000 — 16-bit, short var
   in ax); push eax; push 0xff; push sndStr; call _SoundNoMixer@12.
   else: push 0/push 0xff/push 0xff/push sndStr; call _SingleSound@16. */
extern short curScreen;        /* identity */
extern short timeCompression;  /* identity */
extern char sndStr[];          /* _checkRightButton+0x458 */
extern void __stdcall SoundNoMixer(char *s, short f1, short f2);
extern void __stdcall SingleSound(char *s, short f, unsigned char e, short f2);

void __fastcall ShellButtonSound_q(long n)
{
    if (curScreen == 0x10 && timeCompression == 0x7fff) {
        short f2 = (short)(n / 4);
        f2 -= 0x50;
        SoundNoMixer(sndStr, 0xff, f2);
    } else
        SingleSound(sndStr, 0xff, 0xff, 0);
}
