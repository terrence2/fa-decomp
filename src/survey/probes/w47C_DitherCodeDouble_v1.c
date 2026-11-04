typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern short sat(short s);

/* rva 368176 ?DitherCodeDouble@@YAXPAEPAK0@Z — SVGA24 dither kernel.
   Same 3-call chain / 24-bit accumulator as DitherCode/DitherCodeSingle;
   dst is u32* and each pair of columns lands one dword of two 16-bit
   pixels per table entry half (tab[acc] low word -> dst[0], high -> dst[1]). */
void __cdecl DitherCodeDouble(u8 *d, u32 *dst, u32 *tab)
{
    short n1;
    short v4;
    short v5;
    u16 b;
    u32 acc;
    u32 acc2;
    u32 eA;
    u32 eB;
    u32 n;
    n = 256;
    do {
        v4 = (short)d[4];
        v5 = (short)d[5];
        n1 = (short)-((v4 >> 1) + (v5 >> 2));
        /* column 1 */
        b = (u16)d[0];
        acc = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc = ((acc << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        /* column 2 */
        b = (u16)d[1];
        acc2 = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc2 = ((acc2 << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        eA = tab[acc];
        eB = tab[acc2];
        dst[0] = ((u16)eA) | ((u32)(u16)eB << 16);
        dst[1] = (eA >> 16) | (eB & 0xffff0000u);
        dst += 2;
        /* column 3 */
        b = (u16)d[2];
        acc = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc = ((acc << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        /* column 4 */
        b = (u16)d[3];
        acc2 = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc2 = ((acc2 << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        eA = tab[acc];
        eB = tab[acc2];
        dst[0] = ((u16)eA) | ((u32)(u16)eB << 16);
        dst[1] = (eA >> 16) | (eB & 0xffff0000u);
        dst += 2;
        d += 6;
    } while (--n);
}