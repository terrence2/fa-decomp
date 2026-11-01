// ?_CallMemberFunction2@@YGXPAX00H@Z @ rva 0xd45c0 (7 B, FPO fpo/esp
// params=4 dwords) — MSVC CRT member-call glue, 4-arg brother of the 3-arg
// ?_CallMemberFunction1@@... (wave 17, src/CallMemberFunction1.c) and the
// 2-arg ?_CallMemberFunction0@@... (wave 13). Stack on entry:
// [ret][a2][a3][a4] — pops a2 into eax and a3 into ecx, xchg's the return
// address with eax, jmp eax. No pure C shapes this; naked asm
// (CallMemberFunction1's exact 58 59 87 04 24 ff e0 body, probe b19c_cmf2).
void __declspec(naked) _CallMemberFunction2(void)
{
    __asm {
        pop     eax
        pop     ecx
        xchg    dword ptr [esp], eax
        jmp     eax
    }
}