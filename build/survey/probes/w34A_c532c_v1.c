/* w34A @ rva 0xc532c (dec 807724), 88 B (incl. trailing int3), _WRMonoPalette@12
 * stdcall 3 args. FA per-pixel 16-bit register machine:
 *   bx = (p0+p1+p2)&0xff -> tbl byte -> neg bx (16-bit)
 *   3 channels: ax = p[i] (movzx); ax += bx (16-bit); imul bp = ax*t(16);
 *               p[i] -= (uchar)(prod16 >> 8)   (sub [edi],ah)
 *   p += 3; loop (e2) while --ecx.
 * byteTable base = _DecompressVideoImage@20 + 0x88 (0x4c5110).
 * v1: short-typed locals to drive 16-bit ops, unrolled channels.
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