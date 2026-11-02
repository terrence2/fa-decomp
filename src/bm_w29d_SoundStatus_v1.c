// ?SoundStatus@@YAFXZ @ rva 0x356b0 (64 B) — short __cdecl(void).
// FA: 53 / a0 [_soundOn] / 56 (push esi) / 84 c0 / 57 (push edi) / 75 07 /
// 66 33 c0 / 5f 5e 5b / c3 / 33 ff / bb [mixChanHandle] / 8b 35
// [__imp___AIL_sample_status@4] / L: 8b 03 / 50 / ff d6 / 83 f8 02 / 74 01 /
// 47 / 83 c3 04 / 81 fb [mixChanHandle+0x40] / 72 ea / 66 8b c7 / 5f 5e 5b /
// c3. Tail pad 8d 49 00 (3B).
extern char w29d_sndOn;                    /* _soundOn */
extern void *w29d_mixh[16];                /* ?mixChanHandle@@3PAPAU_SAMPLE@@A */
extern int __declspec(dllimport) __stdcall w29d_ailss(void *h);

short __cdecl w29d_ss(void)
{
    int n;
    void **h;
    int (__stdcall *st)(void *);

    if (!w29d_sndOn)
        return 0;
    n = 0;
    h = w29d_mixh;
    st = w29d_ailss;
    do {
        if (st(h[0]) != 2)
            n++;
        h++;
    } while (h < w29d_mixh + 16);
    return (short)n;
}