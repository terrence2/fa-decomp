// ?_CallMemberFunction1@@YGXPAX00@Z @ rva 0xd45b0 (869808, 7 B, FPO
// cbFrame=0 params=3 dwords) — MSVC CRT member-call glue, 3-arg brother of
// wave-13's ?_CallMemberFunction0@@YGXPAX0@Z. Caller-stack ABI surgery
// emulating __thiscall `o->pmf(arg)` from a plain 3-arg __stdcall helper:
// pop eax takes the RETURN ADDRESS (not a param — corrected read),
// pop ecx takes `this` (the first stack arg), xchg [esp],eax puts the
// retaddr back on top (replacing the popped `this`, which the 3-arg
// ABI slot layout leaves where pmf expects it), and jmp eax tail-jmps
// absolutely to the 2nd arg (pmf) with the 3rd arg left as pmf's outgoing
// stack arg. Sole FA call site: 0xd8f6b in chunk @ 0xd8d9c. No pure C
// shapes this — no construct pops a passed arg (CL cleans outgoing args
// only via ret N), no shape is frameless, and the xchg-with-retaddr +
// absolute jmp has no compiler expression (probes t3_callmbr_v1: closest
// pure C = 17-B framed stdcall with push/call/add; v2.cpp: wave-21 thiscall
// band applies to member functions, not a free stdcall helper — yields ret
// 4 with the call inlined). Keep-asm, verified EXACT (t3_callmbr_cur).
void __declspec(naked) _CallMemberFunction1(void)
{
    __asm {
        pop     eax
        pop     ecx
        xchg    dword ptr [esp], eax
        jmp     eax
    }
}