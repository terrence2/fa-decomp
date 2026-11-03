void __fastcall w32e_66a40_v2(char **pdst, char **psrc)
{
    char *src;
    char *dst;
    int cnt;
    unsigned char b;
    src = *psrc;
    cnt = 0;
    dst = *pdst;
    if ((unsigned char)*src > 1) {
        for (;;) {
            if (cnt >= 3)
                break;
            b = (unsigned char)*src;
            if (b == 10)
                cnt++;
            *dst = (char)b;
            src++;
            dst++;
            if ((unsigned char)*src > 1)
                continue;
            break;
        }
    }
    *psrc = src + 1;
    *pdst = dst;
}