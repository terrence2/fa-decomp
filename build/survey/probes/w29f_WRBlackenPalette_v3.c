// 0xc51d0 _WRBlackenPalette@12 — v3: early local copies of pal/count
#include <string.h>

void __stdcall WRBlackenPaletteX(unsigned char *pal, int count, int black)
{
    unsigned char *p = pal;
    unsigned int scale = 0x100u - black;
    if (scale == 0)
        memset(p, 0, count * 3);
    else if (scale != 0x100u) {
        unsigned char b = (unsigned char)scale;
        for (; count > 0; count--) {
            p[0] = (unsigned char)((p[0] * b) >> 8);
            p[1] = (unsigned char)((p[1] * b) >> 8);
            p[2] = (unsigned char)((p[2] * b) >> 8);
            p += 3;
        }
    }
}
