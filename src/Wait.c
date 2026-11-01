// ?Wait@@YAHXZ @ rva 0x11790 (32 B) — call WaitKey / cmp eax,'q' / jne /
// push 0 / call ErrorExit(0), cdecl cleanup / ret. eax escapes as the
// WaitKey passthrough. The natural C (k live across the ErrorExit call)
// makes CL home k in esi (8b f0 / 8b c6, probe w14a_wait1); CL 4.2 has no
// __declspec(noreturn) to kill the liveness (C2485) — naked asm
// (probe w14a_wait3, byte-exact).
extern int WaitKey(void);
extern void ErrorExit(int code);

__declspec(naked) int Wait_q(void)
{
    __asm {
        call WaitKey
        cmp eax, 0x71
        jne fin
        push 0
        call ErrorExit
        add esp, 4
    fin:
        ret
    }
}