// 0x986e0 — v4: store f160 from a zero temp via edx
extern char w28c_mpArr[];
extern char w28c_ctrlArr[];

void __cdecl w28c_serShutLL(void)
{
    long t, z;

    if (*(long *)(w28c_mpArr + 0x154) == 0) return;
    t = 1L << *(unsigned char *)(w28c_mpArr + 0x164);
    z = 0;
    *(long *)(w28c_mpArr + 0x158) = t;
    w28c_ctrlArr[0x12d] = 0;
    *(long *)(w28c_mpArr + 0x160) = z;
}
