// KEYLCS @ rva 0x11640 — decompiled from FA.EXE (probe d195_lcs.c, byte-exact)
extern char keyboardInitialized[];
extern char keyboardCS[];
__declspec(dllimport) void __stdcall LeaveCriticalSectionX(void *a);
void KEYLCS_q(void)
{
    if (*keyboardInitialized)
        LeaveCriticalSectionX(keyboardCS);
}
