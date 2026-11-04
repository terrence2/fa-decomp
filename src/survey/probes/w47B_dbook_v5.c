// ?DoubleDecode24Book@@YAXPAEPAKGPAUGlobalData@@@Z @ rva 0x57ab0 (816 B)
typedef unsigned char uchar;

short __cdecl F456c00(short x);

void __cdecl DoubleDecode24Book(unsigned char *src, long *dst, char *p3, void *gd)
{
    short w10, w12, w14, w16;
    long n;
    int a, c, b, d1, d2, d3, d4;
    char *g = (char *)gd;

    n = 0x100;
    do {
        if (*(short *)(g + 0xc1ba) != 0) {
            w10 = 0;
            w14 = 0;
            w12 = 0;
        } else {
            w12 = (short)(((int)src[4] << 3) / 5);
            w14 = (short)(((int)src[5] << 3) / 5);
            w10 = -((short)((*(short *)(g + 0xc1b8) + w14) >> 2)
                 + (short)((*(short *)(g + 0xc1b6) + w12) >> 1));
        }
        w16 = (short)(((uchar)src[0] * (short)*(short *)(g + 0xc1b4)) / 16);
        src++;
        b = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        a = F456c00(w16 + w10) << 8;
        c = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        d1 = b | a | c;
        src++;
        w16 = (short)(((uchar)src[-1] * (short)*(short *)(g + 0xc1b4)) / 16);
        b = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        a = F456c00(w16 + w10) << 8;
        c = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        d2 = b | a | c;
        *dst++ = d1;
        *dst++ = d1;
        *dst++ = d2;
        *dst++ = d2;
        if (*(unsigned short *)&p3 != 0) {
            *dst++ = d1;
            *dst++ = d1;
            *dst++ = d2;
            *dst++ = d2;
        }
        w16 = (short)(((uchar)src[0] * (short)*(short *)(g + 0xc1b4)) / 16);
        src++;
        b = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        a = F456c00(w16 + w10) << 8;
        c = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        d3 = b | a | c;
        src++;
        w16 = (short)(((uchar)src[-1] * (short)*(short *)(g + 0xc1b4)) / 16);
        b = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        a = F456c00(w16 + w10) << 8;
        c = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        d4 = b | a | c;
        *dst++ = d3;
        *dst++ = d3;
        *dst++ = d4;
        *dst++ = d4;
        if (*(unsigned short *)&p3 != 0) {
            *dst++ = d3;
            *dst++ = d3;
            *dst++ = d4;
            *dst++ = d4;
        }
        src += 2;
    } while (--n != 0);
}