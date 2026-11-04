// CPUpdateRadar @ rva 0x3e290 — decompiled from FA.EXE (probe d206_cpupd.c, byte-exact)
extern char windowTypes[];
extern char ifmScale[];
extern long currentTicks;
void __stdcall CPUpdateRadar_q(void)
{
    *(long *)(windowTypes + 0x3f4) = 0;
    *(long *)(ifmScale + 4) = currentTicks;
}
