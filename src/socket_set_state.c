// ?socket_set_state@@YAXPAUsocket_state@@W4SOCK_STATE@@@Z @ rva 0xa3140
// (16 B, FPO fpo/esp params=2 dwords) — stores the state enum at
// socket_state+0x10 then TAIL-JUMPS into the unnamed init chunk $FA$_t_
// 4a31e0 (e9 into a params=0 init routine — never returns). asm escape:
// FA's reg plan is value->EAX / base->ECX (89 41 10, store-from-EAX) while
// CL 4.2 canonically picks base->EAX / value->ECX (89 48) for every C
// formulation (socket_set_type/_socket confirm CL's plan); naked asm pins
// FA's plan. The zero-arg __fastcall extern keeps the e9 tail (wave-5 d80).
extern void __fastcall socketSetStateTail(void);
void __declspec(naked) socket_set_state(void)
{
    __asm {
        mov eax, dword ptr [esp+8]
        mov ecx, dword ptr [esp+4]
        mov dword ptr [ecx+0x10], eax
        jmp socketSetStateTail
    }
}