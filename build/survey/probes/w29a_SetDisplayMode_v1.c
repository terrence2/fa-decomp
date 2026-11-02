// 0x1d740 ?SetDisplayMode@CDirDraw@@QAEHKKK@Z @ 0x41d740 (48 B) — v1
// thiscall: this@ecx, 3 stack args, callee pops 0xc (ret 0xc). CL 4.2
// cannot emit a QAE callee from C code, so this is the wave-5 thiscall
// naked-asm escape. Body = SendMessageA(this->[0x278], 0x7e8,
// (a<<16)|b, c) via the ff 15 IAT call.
extern void *w29a_impSendA[];   /* -> __imp__SendMessageA@16 slot */

__declspec(naked) long __stdcall w29a_SetDisplayMode(unsigned long a, unsigned long b, unsigned long c)
{
    __asm {
        mov eax, [esp+0xc]
        mov edx, [esp+4]
        shl edx, 16
        push eax
        mov eax, [esp+0xc]
        mov ecx, [ecx+0x278]
        or edx, eax
        push edx
        push 0x7e8
        push ecx
        call DWORD PTR [w29a_impSendA]
        ret 0xc
    }
}