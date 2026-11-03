/* rva 125488 v4: p as long (loads into eax first like FA), h as char*
 * so h + p is the UNSCALED byte add -> [ecx+eax*1] sib like FA */
char __stdcall w31b_1ea30_v4(long p)
{
    char *h = *(char **)(p + 0x3c);

    return *(long *)(h + p) == 0x4c50;
}