/* ?SoundPoints@@YIXXZ @ rva 0x32fb0 — v2: test before loop inits (FA order
   test/je then si=0, edi=MOD, ebx=1); decl order tries i(m?) reg roles
   FA: counter -> esi, ptr -> edi. */
#pragma pack(1)
typedef struct { char pad0[0x4b]; char b4b; char pad2[8]; } w29c_modspec;
extern w29c_modspec w29c_MOD[];           /* _w29c_MOD -> ?MOD@@3PAUMODSPEC@@A */
extern char w29c_soundOn;                 /* _soundOn (FA bare name) */
extern void __fastcall w29c_SSq(w29c_modspec *m, void *z, char c);     /* ?SoundSetup@@YIXPAUMODSPEC@@0D@Z */
extern void __fastcall w29c_SVPPq(w29c_modspec *m, short i);           /* ?SetVolPitchPan@@YIXPAUMODSPEC@@G@Z */

void SoundPoints_q(void)
{
    short i;
    w29c_modspec *m;
    int one;

    if (!w29c_soundOn)
        return;
    for (i = 0, m = w29c_MOD, one = 1; i < 16; i++, m++) {
        if ((char)m->b4b == (char)one) {
            w29c_SSq(m, 0, 0);
            w29c_SVPPq(m, i);
        }
    }
}