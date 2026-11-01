// _ShutdownKeyboard @ rva 0x112d0 — same guard shape as KEYECS, plus the
// keyboardInitialized = 0 clear after DeleteCriticalSection (probe w11b_11,
// byte-exact; note dis.py skips the c6 05 line — raw-bytes compare caught it)
extern char keyboardInitialized[];
extern char keyboardCS[];
__declspec(dllimport) void __stdcall DeleteCriticalSectionX(void *a);
void ShutdownKeyboard_q(void)
{
    if (*keyboardInitialized)
    {
        DeleteCriticalSectionX(keyboardCS);
        *keyboardInitialized = 0;
    }
}