// NamesShutdown @ rva 0x1c5a0 — decompiled from FA.EXE (probe d198_nsd.c, byte-exact)
extern char items[];
extern char itemPicked[];
extern void __fastcall MMFreePtr(void *p);
void __stdcall NamesShutdown_q(void)
{
    MMFreePtr(*(void **)(items + 4));
    *(unsigned short *)(itemPicked + 0x30) = 0;
    *(long *)(items + 4) = 0;
}
