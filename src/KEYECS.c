// KEYECS @ rva 0x11620 — decompiled from FA.EXE (probe d194_kcs.c, byte-exact)
extern char keyboardInitialized[];
extern char keyboardCS[];
__declspec(dllimport) void __stdcall EnterCriticalSectionX(void *a);
void KEYECS_q(void)
{
    if (*keyboardInitialized)
        EnterCriticalSectionX(keyboardCS);
}
