// _MOUSEShutdown @ rva 0x97e60 (32 B) — mouse-init byte at _vHzMod+0x60
//   (a0 load), clear it (c6 05), then DeleteCriticalSection through the IAT
//   (ff 15) on ?mouse_critical_section@@3U_RTL_CRITICAL_SECTION@@A.
extern char vHzMod[];
extern char mouseCS[];
__declspec(dllimport) void __stdcall DeleteCriticalSectionX(void *a);
void MOUSEShutdown_q(void)
{
    if (vHzMod[0x60])
    {
        vHzMod[0x60] = 0;
        DeleteCriticalSectionX(mouseCS);
    }
}