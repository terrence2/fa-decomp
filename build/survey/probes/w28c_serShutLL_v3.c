// 0x986e0 — v3: named temp, stores after shl
extern char w28c_mpArr[];
extern char w28c_ctrlArr[];

void __cdecl w28c_serShutLL(void)
{
    long t;

    if (*(long *)(w28c_mpArr + 0x154) == 0) return;
    t = 1L << *(unsigned char *)(w28c_mpArr + 0x164);
    *(long *)(w28c_mpArr + 0x158) = t;
    w28c_ctrlArr[0x12d] = 0;
    *(long *)(w28c_mpArr + 0x160) = 0;
}
