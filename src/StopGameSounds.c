// ?StopGameSounds@@YIXXZ @ rva 0x34fb0 (48 B) — kill looping game sounds and
// reset the 8 mix-channel word slots (stride 0xc) to 0xffff.
// FA: call SetupLoopSounds/UpdateLoopSounds/SoundAllOff;
// eax=mixStart (=?musicVolume@@3GA+0x8); do { *w(eax)=0xffff; eax+=0xc }
// while (eax < mixEnd); ret.
extern void __fastcall SetupLoopSoundsQ(void);
extern void __fastcall UpdateLoopSoundsQ(void);
extern void __fastcall SoundAllOffQ(void);
extern char mixStart[];   /* ?musicVolume@@3GA+0x8 */
extern char mixEnd[];     /* ?mixChanHandle@@3PAPAU_SAMPLE@@A */

void __fastcall StopGameSounds_q(void)
{
    unsigned long p;

    SetupLoopSoundsQ();
    UpdateLoopSoundsQ();
    SoundAllOffQ();
    p = (unsigned long)mixStart;
    do {
        *(unsigned short *)p = 0xffff;
        p += 0xc;
    } while (p < (unsigned long)mixEnd);
}
