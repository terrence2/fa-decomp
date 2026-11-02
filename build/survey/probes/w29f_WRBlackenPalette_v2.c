// 0xc51d0 _WRBlackenPalette@12 — v2: /Oy- frame attempt
#include <string.h>

void __stdcall WRBlackenPaletteX(unsigned char *pal, int count, int black)
{
    unsigned int scale = 0x100u - black;
    if (scale == 0)
        memset(pal, 0, count * 3);
    else if (scale != 0x100u) {
        unsigned char b = (unsigned char)scale;
        for (; count > 0; count--) {
            pal[0] = (unsigned char)((pal[0] * b) >> 8);
            pal[1] = (unsigned char)((pal[1] * b) >> 8);
            pal[2] = (unsigned char)((pal[2] * b) >> 8);
            pal += 3;
        }
    }
}
