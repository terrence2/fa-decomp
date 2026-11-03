/* w34A_c532c v2: /Od twin (FA chunk has an ebp frame); short-typed 16-bit
 * ops spelled in declaration order, channels unrolled.
 */
extern unsigned char w34_dvTab[];

void __stdcall WRMonoPalette(unsigned char *p, int n, int t)
{
    short b, dv, ax, pr;

    do {
        b = (unsigned char)(p[0] + p[1] + p[2]);
        dv = 0 - (unsigned short)w34_dvTab[b];

        ax = (unsigned short)p[0] + dv;
        pr = (short)((long)ax * (long)t);
        p[0] = (unsigned char)(p[0] - (unsigned short)((unsigned short)pr >> 8));

        ax = p[1] + dv;
        pr = (short)((long)ax * (long)t);
        p[1] = (unsigned char)(p[1] - (unsigned short)((unsigned short)pr >> 8));

        ax = p[2] + dv;
        pr = (short)((long)ax * (long)t);
        p[2] = (unsigned char)(p[2] - (unsigned short)((unsigned short)pr >> 8));

        p += 3;
    } while (--n != 0);
}