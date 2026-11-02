// 0x7c2e0 (32 B) — v1: fastcall skip-space-or-tab
char *__fastcall w30d_skipws(char *p)
{
    char c;

    for (;;) {
        c = *p;
        if (c == 0)
            return 0;
        if (c == ' ')
            return p;
        if (c == '\t')
            return p;
        ++p;
    }
}