// __cropzeros @ rva 0xd9470 — C v2 (dot-byte reads)
extern volatile char dotByte;    /* ?ctype208=__ctype+0x208 */

void __cdecl cropzerosq(char *buf)
{
    char *end, *p;
    char c;

    p = buf;
    while (*p != 0)
    {
        if (*p == dotByte)
            break;
        p++;
    }
    end = p++;
    if (*end == 0)
        return;
    while (*p != 0)
    {
        c = *p;
        if (c == 'e' || c == 'E')
            break;
        p++;
    }
    end = p--;
    if (*p == '0')
        do
        {
            p--;
        } while (*p == '0');
    if (*p == dotByte)
        p--;
    do
    {
        c = *end;
        p++;
        end++;
        *p = c;
    } while (c != 0);
}
