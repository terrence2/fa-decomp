// 0x7c2e0 (32 B) — v5: break-style single exit
char *__fastcall w30d_skipws5(char *p)
{
    unsigned char c;

    for (;;) {
        c = *p;
        if (c == 0)
            return 0;
        if (c == ' ' || c == '\t')
            break;
        ++p;
    }
    return p;
}