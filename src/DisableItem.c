// DisableItem @ rva 0xcc00 — decompiled from FA.EXE (probe d192_dis.c, byte-exact)
extern int enableHelper(void);
void __fastcall DisableItem_q(short a)
{
    int v = enableHelper();
    if (v != 0)
        *(unsigned char *)(v + 0x10) |= 2;
}
