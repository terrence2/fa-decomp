/* w45G wave-45 batch G: real-C attempt v4 (decl-order flip) for FA rva 0x786b0 ?CompareHints@@YAJPAX0@Z.
 * Nested if-spelling so every nonzero diff jumps to ONE common epilogue
 * (FA's single pop/pop/pop/ret tail), instead of duplicating returns.
 */
#include <string.h>

long w45g_786b0(void *a, void *b)
{
    long d;
    unsigned long ha;
    unsigned long hb;
    unsigned long ha2;
    unsigned long hb2;
    unsigned char ca0;
    unsigned char cb0;

    d = _stricmp((char *)a + 2, (char *)b + 2);
    if (d == 0) {
        hb = *(unsigned long *)((char *)b + 0x13);
        ha = *(unsigned long *)((char *)a + 0x13);
        d = ((hb & 0x1fe00) >> 9) - ((ha & 0x1fe00) >> 9);
        if (d == 0) {
            d = ((hb & 0x1e0) >> 5) - ((ha & 0x1e0) >> 5);
            if (d == 0) {
                d = (hb & 0x1f) - (ha & 0x1f);
                if (d == 0) {
                    hb2 = *(unsigned long *)((char *)b + 0xf);
                    ha2 = *(unsigned long *)((char *)a + 0xf);
                    d = ((hb2 & 0xf800) >> 11) - ((ha2 & 0xf800) >> 11);
                    if (d == 0) {
                        d = ((hb2 & 0x7e0) >> 5) - ((ha2 & 0x7e0) >> 5);
                        if (d == 0) {
                            ca0 = ((unsigned char *)a)[1];
                            cb0 = ((unsigned char *)b)[1];
                            d = ca0 - cb0;
                        }
                    }
                }
            }
        }
    }
    return d;
}