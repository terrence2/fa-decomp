// ?Decode24Book@@YAXPAEPAKPAUGlobalData@@@Z @ rva 0x577f0 (704 B)
typedef unsigned char uchar;

short __cdecl F456c00(short x);

void __cdecl Decode24Book(unsigned char *src, long *dst, void *gd)
{
    short w10, w12, w14, w16;
    long n;
    int b, a, c;
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
        src++;
        w16 = (short)(((uchar)src[-1] * (short)*(short *)(g + 0xc1b4)) / 16);
        src++;
        a = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        c = F456c00(w16 + w10) << 8;
        b = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        *dst = a | c | b;
        dst++;
        w16 = (short)(((uchar)src[-1] * (short)*(short *)(g + 0xc1b4)) / 16);
        a = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        c = F456c00(w16 + w10) << 8;
        b = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        *dst = a | c | b;
        dst++;
        src++;
        w16 = (short)(((uchar)src[-1] * (short)*(short *)(g + 0xc1b4)) / 16);
        a = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        c = F456c00(w16 + w10) << 8;
        b = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        *dst = a | c | b;
        dst++;
        w16 = (short)(((uchar)src[0] * (short)*(short *)(g + 0xc1b4)) / 16);
        src++;
        src += 2;
        a = F456c00(*(short *)(g + 0xc1b6) + w16 + w12) << 16;
        c = F456c00(w16 + w10) << 8;
        b = F456c00(*(short *)(g + 0xc1b8) + w16 + w14);
        *dst = a | c | b;
        dst++;
    } while (--n != 0);
}
