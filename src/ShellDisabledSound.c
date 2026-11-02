// @ShellDisabledSound@4 @ rva 0x8b1f0 (64 B) — FA asm: cmp word [curScreen],0x10
//   / jne / cmp word [timeCompression],0x7fff / jne / push ecx / push 0xff /
//   push offset noMixer str / call SoundNoMixer / ret / push 0 / push 0xff /
//   push 0xff / push offset off str / call SingleSound / ret. Fastcall param
//   (ecx) is pushed as SoundNoMixer's 3rd arg — the sound-family push-ecx arg
//   pass (BasicLinkSound/ButtonSound); sound strings live at
//   checkRightButton+0x470/+0x480 (TO-addend maps). Plain C: 0xff pushes as
//   imm32 68 ff 00 00 00 (int args), 0 as 6a 00; the ==16 / ==0x7fff compares
//   come out of plain C as 66 83/66 81 memory-form cmps.
extern unsigned short curScreen;
extern unsigned short timeCompression;
extern char noMixerStr_[];   // -> _checkRightButton+0x470
extern char offStr_[];       // -> _checkRightButton+0x480
extern int __stdcall SoundNoMixer(char *s, int a, int b);
extern int __stdcall SingleSoundS(char *s, int a, unsigned char c, int d);

int __fastcall ShellDisabledSound_q(int p)
{
    if (curScreen == 16 && timeCompression == 0x7fff)
        return SoundNoMixer(noMixerStr_, 0xff, p);
    return SingleSoundS(offStr_, 0xff, 0xff, 0);
}