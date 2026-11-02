// __NLG_Return @ rva 0xd9075 (43 B = 35 code + 8 cc tail, gap chunk) —
// CRT NLG (nonlocal-goto) return path entered from __CallSettingFrame's
// call chain: save the ScopeIndex-ebp in ebx, pop the fake frame, fetch
// the NLG cookie ([caller ebp+0x10]), re-establish, normalize the cookie
// (0x100 -> 2), call __NLG_Notify1 (performs the NLG notify via the
// pushed ecx), then pop ebx/ecx, leave + ret 12 (skips our 3 args).
// 8x cc tail = census-proven int3 pad.
extern void nlgNotify(void);

void __declspec(naked) NLG_Return_q(void)
{
    __asm {
        mov  ebx, ebp
        pop  ebp
        mov  ecx, dword ptr [ebp+0x10]
        push ebp
        mov  ebp, ebx
        cmp  ecx, 0x100
        jne  Lskip
        mov  ecx, 2
    Lskip:
        push ecx
        call nlgNotify
        pop  ebp
        pop  ecx
        pop  ebx
        _emit 0c9h        // CL 4.2 inline asm silently DROPS `leave` (probe
        ret  12           // w21_probe3) — 0xc9 must be emitted raw
    }
}