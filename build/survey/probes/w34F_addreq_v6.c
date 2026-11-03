extern int memcmp(const void *, const void *, unsigned);

char __cdecl w34f_addreq(void *a, void *b)
{
    unsigned t;
    int m;
    t = *(unsigned short *)a;
    if (*(unsigned short *)b != (unsigned short)t)
        return 0;
    switch (t) {
    case 1:
        return (char)(*(int *)((char *)b + 4) == *(int *)((char *)a + 4));
    case 2:
        return (char)((m = memcmp((char *)a + 8, (char *)b + 8, 6), m == 0));
    default:
        return 0;
    }
}
