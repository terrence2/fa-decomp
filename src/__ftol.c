// __ftol @ rva 0xd49c8 (40 B, gap chunk) — classic CRT double->int
// conversion helper: rounds x87 ST0 toward zero by saving CW, OR-ing in
// 0x0c (chop + invalid-mask... the truncation bits), loading the new CW,
// FISTP to a qword local, restoring CW, returning EDX:EAX. Naked asm
// (x87 register contract); MASM auto-inserts the 9b wait before fstcw
// (probe w21_probe1: fstcw = 9b d9 7d fe) and does NOT wait before
// fldcw/fistp — matching FA's 9b placement exactly; the second 9b is an
// explicit fwait.
void __declspec(naked) ftol_q(void)
{
    __asm {
        push ebp
        mov  ebp, esp
        add  esp, -12
        fstcw word ptr [ebp-2]
        fwait
        mov  ax, word ptr [ebp-2]
        or   ah, 0x0c
        mov  word ptr [ebp-4], ax
        fldcw word ptr [ebp-4]
        fistp qword ptr [ebp-12]
        fldcw word ptr [ebp-2]
        mov  eax, dword ptr [ebp-12]
        mov  edx, dword ptr [ebp-8]
        _emit 0c9h        // NOTE: CL 4.2 inline asm silently DROPS `leave`;
        ret               // the 0xc9 must be emitted raw (probe w21_probe3)
    }
}