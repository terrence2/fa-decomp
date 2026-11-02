// _CpymemXRemap@12 @ rva 0xc2be8 — C v1
extern void *snowHighT[];       /* _snowHigh+0x4 */

void __stdcall CpymemXRemapq(unsigned char *src, unsigned char *dst, int n)
{
    void *tbl;
    unsigned char s;
    int i;

    for (i = 0; i < n; i++)
    {
        s = src[i];
        tbl = snowHighT[s];
        if (s != 0xff)
            dst[i] = ((unsigned char *)tbl)[dst[i]];
    }
}
