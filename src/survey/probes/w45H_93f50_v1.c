/* w45H 0x93f50: slot counter accumulate + vt ack + zero slot dwords */
typedef unsigned long ulong;
typedef int (__cdecl *VT2)(void *);

unsigned char w45H_93f50(void *a)
{
    char *edi = (char *)a;
    ulong esi = *(ulong *)(edi + 0x186);
    ulong ecx0 = *(ulong *)(edi + 0x182);
    *(int *)(ecx0 + 0x56) += (*(int *)(esi + 0xc)) / 8;
    *(int *)(esi + 0xc) = 0;
    if (!(*(VT2 *)(*(ulong *)ecx0 + 8))((void *)edi))
        return 0;
    {
        ulong i = 0;
        while (*(ulong *)(edi + 0x112) > i) {
            *(ulong *)(esi + 0x12 + i * 4) = 0;
            i++;
        }
    }
    *(ulong *)(esi + 0x22) = *(ulong *)(edi + 0xf0);
    *(unsigned char *)(esi + 0x10) = 0;
    return 1;
}