// 0xaf530 _WRGetLayer@8 (96 B) — v2: one-condition loop
extern char w28c_clArr[];

void __stdcall w28c_WRGetLayer(long key, char *out)
{
    char *p;
    long l;

    l = key >> 8;
    if (l < 0) l = 0;
    p = w28c_clArr;
    for (;;) {
        if (*(long *)(p + 0xa) > l) { p += 0x160; continue; }
        if (*(long *)(p + 0xe) < l) { p += 0x160; continue; }
        break;
    }
    if (out) {
        if ((*(char *)(p + 0x160) & 1) || *(long *)(p + 0x16a) > l)
            *out = 0;
        else
            *out = 1;
    }
}
