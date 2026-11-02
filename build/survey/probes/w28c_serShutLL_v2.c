// 0x986e0 ?SER_ShutdownLowLevel@@YAXXZ (48 B) — v2: zero-var reg
extern char w28c_mpArr[];
extern char w28c_ctrlArr[];

void __cdecl w28c_serShutLL(void)
{
    long z = 0;
    if (*(long *)(w28c_mpArr + 0x154) == 0) return;
    *(long *)(w28c_mpArr + 0x158) = 1L << *(unsigned char *)(w28c_mpArr + 0x164);
    w28c_ctrlArr[0x12d] = (char)z;
    *(long *)(w28c_mpArr + 0x160) = z;
}
