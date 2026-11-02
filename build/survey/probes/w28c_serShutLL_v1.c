// 0x986e0 ?SER_ShutdownLowLevel@@YAXXZ (48 B) — v1
extern char w28c_mpArr[];    /* ?mpInfo@@3UMP_INFO@@C */
extern char w28c_ctrlArr[];  /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */

void __cdecl w28c_serShutLL(void)
{
    if (*(long *)(w28c_mpArr + 0x154) == 0) return;
    *(long *)(w28c_mpArr + 0x158) = 1L << *(unsigned char *)(w28c_mpArr + 0x164);
    w28c_ctrlArr[0x12d] = 0;
    *(long *)(w28c_mpArr + 0x160) = 0;
}
