// 0x7c2e0 (32 B) — v2: while condition forms
char *__fastcall w30d_skipws2(char *p)
{
    while (*p) {
        if (*p == ' ' || *p == '\t')
            return p;
        ++p;
    }
    return 0;
}