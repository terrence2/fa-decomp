// CPClearMissile @ rva 0x380e0 — decompiled from FA.EXE (probe d205_cpclr.c, byte-exact)
extern char targetV[];
extern char bombRange[];
extern char numWindowPos[];
void __stdcall CPClearMissile_q(void)
{
    *(unsigned short *)(targetV + 0xd0) = 0;
    *(long *)(bombRange + 0x14) = 0;
    *(long *)(numWindowPos + 0x18) = 0;
}
