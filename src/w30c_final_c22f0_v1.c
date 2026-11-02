/* 0xc22f0 — v1: in-place squeeze of '~' out of a NUL-terminated string
   fastcall: s in ecx */
void __fastcall w30c_strsqueez(char *s)
{
    char *d;
    char c;
    d = s;
    do {
        c = *s;
        if (c != '~')
            *d++ = c;
    } while (*s != 0 && (s++, 1));
}