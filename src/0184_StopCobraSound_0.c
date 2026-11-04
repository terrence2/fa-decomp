// _StopCobraSound@0 @ rva 0x214f0 — call ?SoundAllOff@@YIXXZ / push 0,0,0 /
//   call ?SoundNoMixer@@YGFPADFF@Z / ret; stdcall callee cleans its 8 bytes
//   (probe w8_cobra: e8/6a00 6a00 6a00/e8/c3 exact).
extern void __fastcall SoundAllOff(void);
extern char __stdcall SoundNoMixer(char *s, short a, short b);

void StopCobraSound(void)
{
    SoundAllOff();
    SoundNoMixer(0, 0, 0);
}
