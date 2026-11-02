// __abnormal_termination @ rva 0xd493a (35 B, gap chunk) — CRT EH helper
// asked "is the outermost try-level being unwound?": walks the fs:[0]
// exception-registration list head, compares the current registration's
// handler dword against __global_unwind2+0x20 (81 79 04 mem-immediate
// with the pointer carried as a map'd extern — literal-VA rule), then
// dereferences the scope index chain ([reg+0xc] twice) and compares
// against the registration's try-level. Naked asm: fs: prefix +
// FA-mem-first cmp order are MASM-only.
extern void *unwTableVa[];

void __declspec(naked) abnormal_termination_q(void)
{
    __asm {
        xor  eax, eax
        mov  ecx, dword ptr fs:[0]
        cmp  dword ptr [ecx+4], offset unwTableVa
        jne  Lret
        mov  edx, dword ptr [ecx+0xc]
        mov  edx, dword ptr [edx+0xc]
        cmp  dword ptr [ecx+8], edx
        jne  Lret
        mov  eax, 1
    Lret:
        ret
    }
}