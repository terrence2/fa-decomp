/* rva 0xbbb00 (112 B) - flush-on-tail: fwrite tail buffer, event on error */
void w44F_bbb00(char *s)
{
    char *e;
    unsigned long n;

    e = *(char **)(s + 0x12);
    n = 0x1000 - *(unsigned long *)(e + 4);
    if (n) {
        if (fwrite(*(char **)(e + 0x18), 1, n, *(char **)(e + 0x14)) != n) {
            *(long *)((char *)*(char **)s + 0x14) = 0x24;
            (*(void (__cdecl **)(char *)) *(char **)s)(s);
        }
    }
    fflush(*(char **)(e + 0x14));
    if (*(long *)(*(char **)(e + 0x14) + 0xc) & 0x20) {
        *(long *)((char *)*(char **)s + 0x14) = 0x24;
        (*(void (__cdecl **)(char *)) *(char **)s)(s);
    }
}
