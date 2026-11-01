// @F24ToPA@4 @ rva 0xc29d0 (24 B; gap chunk — no .debug$F/FPO record) —
// fixed-24 altitude -> PA-units scale with round-to-nearest:
//   imul eax,ecx,0x3e8 (x * 1000) / cdq / add eax,0x2bf / adc edx,0
//   (64-bit +703 half-divisor round-up) / mov ecx,0x57e (1406 = 2*703) /
//   idiv ecx / ret
// C-unreachable: CL 4.2 folds constant division into a magic-multiply and
// its multiply plans are register-canonical — naked asm escape, same family
// as wave 14's LMultDiv256/LFMult naked multiplies (probe b18c_F24ToPA
// byte-exact first try, zero relocs).
int __declspec(naked) __fastcall F24ToPA(int x)
{
    __asm
    {
        imul eax, ecx, 1000
        cdq
        add eax, 0x2bf
        adc edx, 0
        mov ecx, 0x57e
        idiv ecx
        ret
    }
}
