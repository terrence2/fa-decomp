// _VIEWInTransition@0 @ rva 0xe6a0 (36 B code + 12 B pad) — char stdcall
// gate: window start/end dwords flanking _timerTicks,
//   mov eax,[wnd end] / mov ecx,[_timerTicks] / cmp ecx,eax / jl ret0
//   mov eax,[wnd start] / mov ecx,[_timerTicks] / cmp ecx,eax / jge ret0
//   mov al,1 / ret / xor al,al / ret.
// Naked asm escape: every C form (plain guards, ||, &&, mirrored operands —
// probes w16c_4 rounds 1-5) loads timerTicks into EAX via a1 and the window
// dword into ECX via 8b 0d (cmp mirrored, jcc polarity per window reload);
// FA keeps the window in EAX (a1) and RELOADS _timerTicks into ECX for both
// tests.  Addends +0xcc/+0xc8 live in the map TOs (double-addend rule); MASM
// "mov eax, dword ptr sym" emits FA's a1 moffs.
extern long timerTicks;
extern char viewTransEnd[];
extern char viewTransStart[];

char __declspec(naked) __stdcall VIEWInTransition(void)
{
    __asm {
        mov eax, dword ptr viewTransEnd
        mov ecx, timerTicks
        cmp ecx, eax
        jl L0
        mov eax, dword ptr viewTransStart
        mov ecx, timerTicks
        cmp ecx, eax
        jge L0
        mov al, 1
        ret
L0:
        xor al, al
        ret
    }
}