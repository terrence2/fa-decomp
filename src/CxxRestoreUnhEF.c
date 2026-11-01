// ?__CxxRestoreUnhandledExceptionFilter@@YAXXZ @ rva 0xdf350 (13 B) —
// hand the C++ runtime's saved filter back to the OS at teardown:
// eax = old filter (dword at 0x588ba4 = ?dbaseLow@@3PAEA+0x2874, written by
// __CxxSetUnhandledExceptionFilter at 0x4df2e8), push, call
// SetUnhandledExceptionFilter off the IAT, ret. A dllimport call whose
// argument is a memory load gets a dead push ebx/pop ebx wrap in C —
// naked-asm escape (probe w13c_cxxr1 vs w13c_cxxr2 exact).
extern unsigned long oldCxxFilter[];
extern void *impSetUnhEF[];

void __declspec(naked) _CxxRestoreUnhandledExceptionFilter(void)
{
    __asm {
        mov     eax, dword ptr [oldCxxFilter]
        push    eax
        call    dword ptr [impSetUnhEF]
        ret
    }
}