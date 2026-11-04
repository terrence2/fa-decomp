/* w33B_330b0_v3.c -- arg11 AND arg12 unsigned short (FA pushes 68 ffff0000 both) */
extern short __stdcall w33b_soundon(char *name, short a2, short a3, short a4,
    short a5, short a6, short a7, short a8, short a9, short a10,
    unsigned short a11, unsigned short a12, short a13, short a14, short a15);

short __stdcall w33b_singlesound(char *p1, short p2, unsigned char p3, short p4)
{
    return w33b_soundon(p1, (short)p3, p2, 0, 0, (short)-1, (short)-1, 0, 0,
        (short)-1, (unsigned short)-1, (unsigned short)-1, p4, 0, (short)-1);
}