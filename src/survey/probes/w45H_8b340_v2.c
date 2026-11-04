/* w45H 0x8b340: unlock/flush resource block (vt cmds 0x29/0x74 + byte patch) */
typedef unsigned long ulong;
typedef void (__stdcall *VF0)(void *);
typedef void (__stdcall *VF2)(void *, long);

extern int x485040(ulong, ulong, ulong);    /* _x485040 = $FA$_t_485040 */

unsigned char w45H_8b340(void *arg)
{
    char *edi = (char *)arg;
    char *esi = *(char **)(edi + 0x12);
    ulong r;
    r = (ulong)x485040(*(ulong *)(esi + 0x20), *(ulong *)(esi + 0x1c), 0x1000);
    if (r == 0) {
        if (*(unsigned char *)(esi + 0x24)) {
            ulong vt;
            vt = *(ulong *)edi;
            *(ulong *)(vt + 0x14) = 0x29;
            ((VF0 *)vt)[0](edi);
            vt = *(ulong *)edi;
            *(ulong *)(vt + 0x14) = 0x74;
            ((VF2 *)vt)[1](edi, -1);
        }
        {
            ulong p = *(ulong *)(esi + 0x20);
            *(unsigned char *)p = 0xff;
            p = *(ulong *)(esi + 0x20);
            *(unsigned char *)(p + 1) = 0xd9;
        }
        r = 2;
    }
    {
        ulong out;
        out = *(ulong *)(esi + 0x20);
        *(ulong *)esi = out;
        *(ulong *)(esi + 4) = r;
    }
    *(unsigned char *)(esi + 0x24) = 0;
    return 1;
}
