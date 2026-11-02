// 0xaf530 — v5: decl order l first (reg steering: l in ecx, p in eax)
extern char w28c_clArr[];

void __stdcall w28c_WRGetLayer(long key, char *out)
{
    long l;
    char *p;

    l = key;
    l >>= 8;
    if (l < 0) l = 0;
    p = w28c_clArr;
    for (;;) {
        if (*(long *)(p + 0xa) <= l && *(long *)(p + 0xe) >= l) break;
        p += 0x160;
    }
    if (out) {
        if ((*(unsigned char *)(p + 0x160) & 1) == 0 && *(long *)(p + 0x16a) <= l)
            *out = 1;
        else
            *out = 0;
    }
}
