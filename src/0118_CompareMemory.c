// ?CompareMemory@@YAHPBX0I@Z @ rva 0x12b80 — C v1 (CRT memcmp shape)
int __cdecl cmpmemq(const void *p1, const void *p2, unsigned long n)
{
    const unsigned char *a;
    const unsigned char *b;

    if (n == 0)
        return 0;
    a = (const unsigned char *)p1;
    b = (const unsigned char *)p2;
    while (--n != 0)
    {
        if (*a != *b)
            break;
        a++;
        b++;
    }
    return (int)*a - (int)*b;
}
