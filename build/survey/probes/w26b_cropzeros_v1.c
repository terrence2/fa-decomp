// __cropzeros @ rva 0xd9470 — C v1 (CRT cvt.c shape)
extern unsigned char deccharG[];

void __cdecl cropzerosq(char *buf)
{
    char *end;
    char *p;

    if (*buf == 0)
        goto done;
    p = buf;
    while (*p != 0 && *p != (char)*deccharG)
        p++;
    if (*p == 0)
        goto done;
    end = p;
    p++;
    while (*p != 0 && *p != 'e' && *p != 'E')
        p++;
    buf = p;
    p--;
    while (*p == '0')
    {
        if (*(p - 1) != '0')
            break;
        p--;
    }
    if (*p == (char)*deccharG)
        p--;
    p++;
    for (;;)
    {
        char c = *end;
        p++;
        end++;
        *p = c;
        if (c == 0)
            break;
    }
done:
    ;
}
