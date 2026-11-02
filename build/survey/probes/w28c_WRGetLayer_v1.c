// 0xaf530 _WRGetLayer@8 (96 B) — v1
extern char w28c_clArr[];  /* ?curLayers@@3PAULAYER@@A (LAYER stride 0x160) */

void __stdcall w28c_WRGetLayer(long key, char *out)
{
    char *p;
    long l;

    l = key >> 8;
    if (l < 0) l = 0;
    p = w28c_clArr;
    for (;;) {
        if (*(long *)(p + 0xa) <= l && *(long *)(p + 0xe) >= l) break;
        p += 0x160;
    }
    if (out) {
        if ((*(unsigned char *)(p + 0x160) & 1) != 0)
            *out = 0;
        else if (*(long *)(p + 0x16a) > l)
            *out = 0;
        else
            *out = 1;
    }
}
