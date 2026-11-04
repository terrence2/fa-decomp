long __stdcall w43H_6dh(void *a2, long *arg2, long unused)
{
    long *pt = arg2;
    char *ps = (char *)a2;
    long d1, d2;
    d1 = (long)*(signed char *)(ps + 3) << 12;
    pt[0] += d1;
    d2 = (long)*(signed char *)(ps + 4) << 12;
    pt[1] += d2;
    pt[2] += (long)*(signed char *)(ps + 5) << 12;
    if (d2 < 0)
        pt[1] = 0;
    return 0;
}
