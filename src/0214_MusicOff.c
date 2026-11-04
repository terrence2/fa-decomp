// ?MusicOff@@YIXXZ @ rva 0x32730 (206640, 48 B) — fastcall void(void):
//   mov al,[0x4e75f0] / test / je / mov eax,[musicPlaying] / test / je /
//   mov eax,[musicSeqHandle] / push eax / call [__imp___AIL_release_
//   sequence_handle@4] / mov [musicPlaying],0 / pop ebx / ret. FA pushes the
//   (unused) ebx callee-save up front — steering first, else patch-insert.
extern unsigned char w27c_muOn;      /* =$FA$_d_4e7000+0x5f0 */
extern void *w27c_musicPlaying;      /* =?musicPlaying@@3PAXA */
extern void *w27c_musicSeqHandle;    /* =?musicSeqHandle@@3PAU_SEQUENCE@@A */
extern void __declspec(dllimport) __stdcall w27c_ailrel(void *h);

void __stdcall w27c_MusicOff(void)
{
    if (w27c_muOn && w27c_musicPlaying) {
        w27c_ailrel(w27c_musicSeqHandle);
        w27c_musicPlaying = 0;
    }
}
