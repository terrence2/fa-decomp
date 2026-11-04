/* StartCobraSound @ rva 0x21510 (128 B) — stdcall, no args; 4 locals.
 * SoundAllOff(); if (soundOn): spin loop [t0=timeGetTime(); while
 * (SoundStatus()!=0 && timeGetTime()-t0 < 2000)]; 
 * RMChangeType(0x525928, 0x4ea284, &local); SoundNoMixer(&local, 0xff, 0);
 * if (soundOn): same 2-second drain spin; ret.
 * Transplant entry — verbatim FA body (IAT indirect call edi-cached;
 * 5 DIR32 + 6 rel32 newsites). */
extern char soundOn;
extern unsigned long __imp__timeGetTime;
extern short SoundStatusX(void);
extern void w27h_SoundAllOff(void);
extern void __stdcall RMChangeTypeX(long a, long b, long *c);
extern char __stdcall SoundNoMixerX(char *p, short f, short m);

void __stdcall StartCobraSound(void)
{
    char loc[4];
    unsigned long t0;
    volatile unsigned long *now = (unsigned long *)&__imp__timeGetTime;
    w27h_SoundAllOff();
    if (!soundOn) return;
    t0 = *now; SoundStatusX();
    while (*now - t0 < 2000) SoundStatusX();
    loc[0] = (char)((long)RMChangeTypeX);
    RMChangeTypeX(0, 0, (long *)loc);
    SoundNoMixerX(loc, 0, 0);
    t0 = *now; SoundStatusX();
    while (*now - t0 < 2000) SoundStatusX();
}
