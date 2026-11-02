/* ?SoundPoints@@YIXXZ @ rva 0x32fb0 (80 B; 67 code + 13 pad).
   a0 [_soundOn] / push ebx / push esi / push edi interleaved with the
   test / je; loop i (si) 0..15 over MOD (edi, stride 0x54): if
   [edi+0x4b]==1 (ebx holds the 1) { SoundSetup(edi,0,0);
   SetVolPitchPan(edi,si); }  -- YI fastcall spell for the two calls. */
#pragma pack(1)
typedef struct { char pad0[0x4b]; char b4b; char pad2[8]; } w29c_modspec;
extern w29c_modspec w29c_MOD[];           /* _w29c_MOD -> ?MOD@@3PAUMODSPEC@@A */
extern char w29c_soundOn;                 /* _soundOn (FA bare name) */
extern void __fastcall w29c_SSq(w29c_modspec *m, void *z, char c);     /* ?SoundSetup@@YIXPAUMODSPEC@@0D@Z */
extern void __fastcall w29c_SVPPq(w29c_modspec *m, short i);           /* ?SetVolPitchPan@@YIXPAUMODSPEC@@G@Z */

void SoundPoints_q(void)
{
    w29c_modspec *m;
    short i;
    int one;

    i = 0;
    m = w29c_MOD;
    one = 1;
    if (!w29c_soundOn)
        return;
    for (; i < 16; i++, m++) {
        if ((char)m->b4b == (char)one) {
            w29c_SSq(m, 0, 0);
            w29c_SVPPq(m, i);
        }
    }
}