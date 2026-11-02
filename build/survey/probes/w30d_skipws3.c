// 0x7c2e0 (32 B) — v3: for-loop with single load via unsigned char local
char *__fastcall w30d_skipws3(char *p)
{
    unsigned char c;

    while (c = *p) {
        if (c == ' ')
            return p;
        if (c == '\t')
            return p;
        ++p;
    }
    return 0;
}