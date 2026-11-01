// @GG_ShutdownMode@0 @ rva 0x5d2e0 (48 B) — thiscall Destroy on the primary
// surface then frees it, with the c7 05 lpPrimarySurface=NULL store scheduled
// BETWEEN the call and its add esp,4 — asm escape (probe w12a_11 byte-exact).
extern long ggpSrf;
extern void __fastcall ggRelease(long o);
extern void __cdecl ggFree(long p);

__declspec(naked) void __stdcall GG_ShutdownMode_q(void)
{
    __asm {
        push esi
        mov esi, ggpSrf
        test esi, esi
        je Lexit
        mov ecx, esi
        call ggRelease
        push esi
        call ggFree
        mov ggpSrf, 0
        add esp, 4
    Lexit:
        pop esi
        ret
    }
}
