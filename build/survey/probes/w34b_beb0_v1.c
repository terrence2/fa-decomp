/* rva 0xbeb0 (48816), 48 B - scan for byte <= 1, return 0 or p+1. */
unsigned char * __stdcall w34b_beb0(unsigned char *p)
{
    while (*p > 1)
        p++;
    if (*p == 0)
        return 0;
    return p + 1;
}