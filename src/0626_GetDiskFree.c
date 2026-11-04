/* _GetDiskFree @ rva 0x78c70 (dec 494704), size 0x70:
 * FA: buf = *(unsigned long*)&theXtemplate ("X:\\" dword @CDPATH+0x148);
 * if (arg1) buf.byte0 = arg1low+0x41; GetDiskFreeSpaceA(&buf,&n1,&n2,&n3,&n4);
 * r!=1 -> -1; total = n2*n3*n1; (long)total<0 -> 0x7fffffff; return total.
 */
extern unsigned long w44B_xbuf;  /* "X:\" template dword (CDPATH+0x148) */
__declspec(dllimport) unsigned long __stdcall GetDiskFreeSpaceA(
    char *root, unsigned long *spc, unsigned long *bps,
    unsigned long *fc, unsigned long *tc);

unsigned long __stdcall GetDiskFree(int i)
{
    unsigned long buf = w44B_xbuf;
    char *root = 0;                  /* i == 0: current drive (NULL) */
    unsigned long n1, n2, n3, n4;
    unsigned long r;
    long total;
    if (i != 0) {
        root = (char *)&buf;
        *(unsigned char *)&buf = (unsigned char)i + 0x41;
    }
    r = GetDiskFreeSpaceA(root, &n1, &n2, &n3, &n4);
    if (r != 1)
        return 0xffffffff;
    total = (long)(n2 * n3 * n1);
    if (total < 0)
        return 0x7fffffff;
    return (unsigned long)total;
}