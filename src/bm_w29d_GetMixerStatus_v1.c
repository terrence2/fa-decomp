// ?GetMixerStatus@@YAFXZ @ rva 0x35670 (64 B) — short __cdecl(void).
// FA: 53 / a0 [_soundOn] / 84 c0 / 75 05 (jne body) / 66 33 c0 / 5b / c3 /
// a0 [noMixLeft+0x4b] / 84 c0 / 75 16 / a1 [mixChanHandle] / 50 / ff 15
// [__imp___AIL_sample_status@4] / 83 f8 02 / 75 05 / 66 33 c0 / 5b / c3 /
// 66 b8 01 00 / 5b / c3. Dead push/pop ebx around (unused reg save).
extern char w29d_sndOn;               /* _soundOn */
extern char w29d_nmlB;                /* ?noMixLeft@@3UMODSPEC@@A+0x4b */
extern void *w29d_mixh[16];           /* ?mixChanHandle@@3PAPAU_SAMPLE@@A */
extern int __declspec(dllimport) __stdcall w29d_ailss(void *h);

short __cdecl w29d_gms(void)
{
    if (!w29d_sndOn)
        return 0;
    if (!w29d_nmlB) {
        if (w29d_ailss(w29d_mixh[0]) == 2)
            return 0;
    }
    return 1;
}