/* rva 0xbeb0 (48816), 48 B - v2: invert the zero-test; scan for byte <= 1. */
unsigned char * __stdcall w34b_beb02(unsigned char *p)
{
    while (*p > 1)
        p++;
    if (*p != 0)
        return p + 1;
    return 0;
}