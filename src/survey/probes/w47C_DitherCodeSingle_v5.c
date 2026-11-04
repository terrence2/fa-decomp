typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern short sat(short s);

struct DCS_S {
    short pad;   /* FA local slot 0 — never touched */
    short n1;
    short v4;
    short v5;
};

/* rva 366896 ?DitherCodeSingle@@YAXPAEPAG0@Z — SVGA15 dither kernel */
void __cdecl DitherCodeSingle(u8 *d, short *dst, u32 *tab)
{
    struct DCS_S s;
    u32 col;
    u32 n;
    u32 acc;
    u16 b;
    n = 256;
    do {
        s.v4 = (short)d[4];
        b = (u16)d[0];
        d++;
        d++;
        s.v5 = (short)d[3];
        s.n1 = (short)-((s.v4 >> 1) + (s.v5 >> 2));
        /* pixel pair 1: columns b=d[0], b=d[1] */
        acc = ((sat(s.v4 + b) & ~7) * 4) | ((u32)(u16)sat(s.n1 + b) >> 3);
        b = (u16)(b + s.v5);
        acc = ((acc << 5) | ((u32)(u16)sat(b) >> 3)) >> 1;
        col = (u8)tab[acc];
        b = (u16)d[-1];
        acc = ((sat(s.v4 + b) & ~7) * 4) | ((u32)(u16)sat(s.n1 + b) >> 3);
        b = (u16)(b + s.v5);
        acc = ((acc << 5) | ((u32)(u16)sat(b) >> 3)) >> 1;
        *(u16 *)dst = (u16)(((u8)tab[acc] << 8) | col);
        dst += 2;
        /* pixel pair 2: columns b=d[2], b=d[3] */
        b = (u16)d[-2];
        acc = ((sat(s.v4 + b) & ~7) * 4) | ((u32)(u16)sat(s.n1 + b) >> 3);
        b = (u16)(b + s.v5);
        acc = ((acc << 5) | ((u32)(u16)sat(b) >> 3)) >> 1;
        col = (u8)tab[acc];
        b = (u16)d[-1];
        acc = ((sat(s.v4 + b) & ~7) * 4) | ((u32)(u16)sat(s.n1 + b) >> 3);
        b = (u16)(b + s.v5);
        acc = ((acc << 5) | ((u32)(u16)sat(b) >> 3)) >> 1;
        *(u16 *)dst = (u16)(((u8)tab[acc] << 8) | col);
        dst += 2;
        d += 2;
    } while (--n);
}