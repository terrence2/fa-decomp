/* w45H 0x901c0: alloc+init 0x580 object (vt[0] alloc, table fills, copy) */
typedef unsigned long ulong;
void *memset(void *, int, unsigned long);
void *memcpy(void *, const void *, unsigned long);

typedef int (*FN)(void *, ulong, ulong);
typedef FN *VTP;

ulong w45H_901c0(void *arg)
{
    char *esi = (char *)arg;
    VTP vt = *(VTP *)(esi + 4);
    ulong res = (ulong)vt[0](arg, 1, 0x580);
    char *edx;
    int i;
    memset((void *)res, 0, 0x100);
    edx = (char *)res + 0x100;
    *(ulong *)(esi + 0x10e) = (ulong)edx;
    for (i = 0; i <= 0xff; i++)
        edx[i] = (char)i;
    memset((void *)((char *)edx + 0x100), 0xff, 0x180);
    edx += 0x80;
    memset((void *)((char *)edx + 0x200), 0, 0x180);
    memcpy((void *)((char *)edx + 0x380), (void *)(res + 0x100), 0x80);
    return res;
}