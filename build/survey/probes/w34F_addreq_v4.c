extern int memcmp(const void *, const void *, unsigned);

char __cdecl w34f_addreq(void *a, void *b)
{
    unsigned short t;
    int m;
    t = *(unsigned short *)a;
    if (*(unsigned short *)b != t)
        return 0;
    if (t == 1)
        return (char)(*(int *)((char *)b + 4) == *(int *)((char *)a + 4));
    if (t == 2)
        return (char)((m = memcmp((char *)a + 8, (char *)b + 8, 6), m == 0));
    return 0;
}
