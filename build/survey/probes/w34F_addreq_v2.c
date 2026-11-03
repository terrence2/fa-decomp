extern int memcmp(const void *, const void *, unsigned);

char __cdecl w34f_addreq(void *a, void *b)
{
    unsigned short t;
    int m;
    t = *(unsigned short *)a;
    if (*(unsigned short *)b != t)
        return 0;
    return (char)(((t & 0xffff) == 1)
        ? (*(int *)((char *)a + 4) == *(int *)((char *)b + 4))
        : (((t & 0xffff) == 2)
            ? (m = memcmp((char *)a + 8, (char *)b + 8, 6), m == 0)
            : 0));
}