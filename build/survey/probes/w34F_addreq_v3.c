extern int memcmp(const void *, const void *, unsigned);

char __cdecl w34f_addreq(void *a, void *b)
{
    unsigned t;
    t = *(unsigned short *)a;
    if (*(unsigned short *)b != t)
        return 0;
    if (t == 1)
        return (char)(*(int *)((char *)b + 4) == *(int *)((char *)a + 4));
    return (char)(memcmp((char *)a + 8, (char *)b + 8, 6) == 0);
}
