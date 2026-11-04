// ?SoundAllOff@@YIXXZ @ rva 0x33870 (211056, 64 B) — fastcall void(void):
//   push esi / mov al,[soundOn] / test / je L / p=MOD+0x2e do {*p=0xffff;
//   p+=0x54} while (p<MOD+0x56e) / xor esi,esi / do {ecx=esi; inc esi; call
//   ?SoundRelease@@YIXF@Z} while (esi<0x10) / push 0,0,0 / call
//   ?SoundNoMixer@@YGFPADFF@Z / pop esi / ret.
extern unsigned char w27c_soundOn;   /* =_soundOn */
extern unsigned short w27c_volA[];   /* =?MOD@@3PAUMODSPEC@@A+0x2e */
extern unsigned short w27c_volEnd[]; /* =?MOD@@3PAUMODSPEC@@A+0x56e */
extern void __fastcall w27c_SoundRelease(short s);
extern char __stdcall w27c_SoundNoMixer(char *a, short b, short c);

void __stdcall w27c_SoundAllOff(void)
{
    unsigned short *p;
    int i;
    if (w27c_soundOn) {
        p = w27c_volA;
        do {
            *p = 0xffff;
            p += 0x2a;
        } while (p < w27c_volEnd);
        for (i = 0; i < 0x10; i++)
            w27c_SoundRelease(i);
        w27c_SoundNoMixer(0, 0, 0);
    }
}
