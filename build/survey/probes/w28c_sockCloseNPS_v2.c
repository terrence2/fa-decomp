// 0xa2fb0 — v2 early-return shape
extern char w28c_sockArr[];
extern void __cdecl w28c_sockCloseX(unsigned long h);

void __cdecl w28c_sockCloseNPS(void)
{
    if (*(long *)(w28c_sockArr + 0x418) == -1L) return;
    w28c_sockCloseX(*(unsigned long *)(w28c_sockArr + 0x418));
    if (*(long *)(w28c_sockArr + 0x41c) == -1L) return;
    w28c_sockCloseX(*(unsigned long *)(w28c_sockArr + 0x41c));
    if (*(long *)(w28c_sockArr + 0x420) == -1L) return;
    w28c_sockCloseX(*(unsigned long *)(w28c_sockArr + 0x420));
}
