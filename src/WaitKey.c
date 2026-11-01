// _WaitKey @ rva 0x126c0 (48 B) — imp-Sleep parked in esi (8b 35 IAT
// load); loop: call GetKey / test / jne exit / mov eax,[waitCounter] /
// push 0 / inc eax / moffs store / call esi / jmp loop; pop esi / ret.
// FA's a1/40/a3 reg-inc dance on a loaded-from-mem counter is asm-only
// (C foldss to ff 05 mem-inc, w14a_wk2); the IAT pointer in esi then
// ff d6 call avoids ff 15 too.
extern char waitCounter[];
extern int GetKey(void);
extern void *impSleepIAT;       // __imp__Sleep

__declspec(naked) int WaitKey_q(void)
{
    __asm {
        push esi
        mov esi, dword ptr [impSleepIAT]
    l1:
        call GetKey
        test eax, eax
        jne fin
        mov eax, dword ptr [waitCounter]
        push 0
        inc eax
        mov dword ptr [waitCounter], eax
        call esi
        jmp l1
    fin:
        pop esi
        ret
    }
}