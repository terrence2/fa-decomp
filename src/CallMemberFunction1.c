// ?_CallMemberFunction1@@YGXPAX00@Z @ rva 0xd45b0 (7 B, FPO fpo/esp
// params=3 dwords) — MSVC CRT member-call glue, 3-arg brother of
// wave-13's ?_CallMemberFunction0@@YGXPAX0@Z. Stack on entry: [ret][a2][a3]
// — pops a2 into eax and a3 into ecx, xchg's the return address with eax,
// jmp eax. No pure C shapes this; naked asm (CallMemberFunction0's exact
// 58 59 87 04 24 ff e0 body).
void __declspec(naked) _CallMemberFunction1(void)
{
    __asm {
        pop     eax
        pop     ecx
        xchg    dword ptr [esp], eax
        jmp     eax
    }
}