/* SeqFadeOut v3: min-compare BEFORE the memcpy (FA order; FA's tgt=ebp). */
extern unsigned char curPalette[];
extern unsigned char realPalette[];
extern void __stdcall WRBlackenPalette(unsigned char *, unsigned long, long);
void *__cdecl memcpy(void *, const void *, unsigned long);

unsigned char __cdecl SeqFadeOut(unsigned short step, unsigned short tgt)
{
    unsigned short m;
    long r;
    m = step;
    if (tgt < m)
        m = tgt;
    memcpy(curPalette, realPalette, 0x300);
    r = ((m & 0xffff) << 8) / (tgt & 0xffff);
    WRBlackenPalette(curPalette, 0x100, r);
    return tgt <= m;
}