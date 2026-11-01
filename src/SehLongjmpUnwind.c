// _seh_longjmp_unwind@4 @ rva 0xd4b35 (27 B, gap chunk — no FPO record) —
// stdcall; the frame is [esp+8] = EXCEPTION_REGISTRATION record pointer in
// ecx, and __local_unwind2's contract needs ebp = [ecx] (frame->next)
// BEFORE the call, then the two longjmp-unwind args pushed as [ecx+0x1c]
// (arg2) first, [ecx+0x18] (arg1) second, caller-clean 8, pop ebp, ret 4.
// The dead-to-C ebp store is the callee's register contract — naked asm.
extern void __cdecl _local_unwind2(long frame, long trylevel);

void __declspec(naked) __stdcall _seh_longjmp_unwind(void)
{
    __asm {
        push ebp
        mov  ecx, [esp+8]
        mov  ebp, [ecx]
        mov  eax, [ecx+0x1c]
        push eax
        mov  eax, [ecx+0x18]
        push eax
        call _local_unwind2
        add  esp, 8
        pop  ebp
        ret 4
    }
}