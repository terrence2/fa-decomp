// __cropzeros @ rva 0xd9470 — C v3 (do-while forms so each loop keeps
// FA's rotated bottom-test `cmp [edx],0 / jne body`; pre-tests hoisted
// once by hand as ifs)
extern volatile char dotByte;    /* ?ctype208=__ctype+0x208 */

void __cdecl cropzerosq(char *buf)
{
    char *p, *end;
    unsigned char c;

    p = buf;
    if (*p != 0)
    {
        do
        {
            if (*p == dotByte)
                break;
            p++;
        } while (*p != 0);
    }
    end = p++;
    if (*end == 0)
        return;
    if (*p != 0)
    {
        do
        {
            c = *p;
            if (c == 'e' || c == 'E')
                break;
            p++;
        } while (*p != 0);
    }
    end = p--;
    if (*p == '0')
    {
        do
        {
            p--;
        } while (*p == '0');
    }
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