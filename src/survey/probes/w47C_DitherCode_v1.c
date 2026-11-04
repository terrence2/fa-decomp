typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern short sat(short s);

/* rva 367456 ?DitherCode@@YAXPAEPAK0@Z — SVGA16 dither kernel */
void __cdecl DitherCode(u8 *d, u32 *dst, u32 *tab)
{
    short n1;
    short v4;
    short v5;
    u16 b;
    u32 acc;
    u32 acc2;
    u32 col;
    u32 n;
    n = 256;
    do {
        v4 = (short)d[4];
        d++;
        d++;
        v5 = (short)d[3];
        n1 = (short)-((v4 >> 1) + (v5 >> 2));
        /* pair 1, column A */
        b = (u16)d[-2];
        acc = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc = ((acc << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        /* pair 1, column B */
        b = (u16)d[-1];
        acc2 = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc2 = ((acc2 << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        col = (u32)tab[acc] | ((u32)tab[acc2] << 16);
        *(u32 *)dst = (u16)col | (col & 0xffff0000u);
        dst += 2;
        /* pair 2 */
        b = (u16)d[-2];
        acc = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc = ((acc << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        b = (u16)d[-1];
        acc2 = ((sat(b + v4) & 0xfffffff8u) * 4) | ((u32)(u16)sat(b + n1) >> 3);
        acc2 = ((acc2 << 5) | ((u32)(u16)sat(b + v5) >> 3)) >> 1;
        *(u32 *)dst = ((u32)tab[acc] >> 16) | (tab[acc2] & 0xffff0000u);
        dst += 2;
        d += 2;
    } while (--n);
}