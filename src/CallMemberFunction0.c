// ?_CallMemberFunction0@@YGXPAX0@Z @ rva 0xd45a0 (7 B, FPO fpo/esp,
// params=2 dwords) — MSVC CRT member-call glue. Stack on entry: [fn][obj]
// [ret]; pops fn into eax and obj into ecx, xchg's the return address with
// fn, and jmp eax — so the "call" transfers to the caller with fn parked on
// the stack where the callee's return will pick it up. No pure C shapes
// this; naked asm (probe w13c_cmfn1 exact: 58 59 87 04 24 ff e0).
void __declspec(naked) _CallMemberFunction0(void)
{
    __asm {
        pop     eax
        pop     ecx
        xchg    dword ptr [esp], eax
        jmp     eax
    }
}