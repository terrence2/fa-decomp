// ?ScoreOff@@YIXXZ @ rva 0x327a0 (48 B) — FA asm: a0 [sndEnable 0x4e75f0]/
//   test al,al/74 je/ c7 05 [scoreStart],0 / 8a 0d [dMusic] / 84 c9 / 74 05 /
//   e9 jmp ?DMusicOff@@YIXXZ / e9 jmp ?MusicOff@@YIXXZ / ret.
extern char sndEnableQ;      /* $FA$_d_4e7000+0x5f0 */
extern void *scoreStart;     /* ?scoreStart@@3PAXA */
extern char dMusic;          /* _dMusic */
void __fastcall DMusicOff_q(void);
void __fastcall MusicOff_q(void);
void ScoreOff_q(void)
{
    if (sndEnableQ) {
        scoreStart = 0;
        if (dMusic)
            DMusicOff_q();
        else
            MusicOff_q();
    }
}
