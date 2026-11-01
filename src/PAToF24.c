// @PAToF24@4 @ rva 0xc29e8 (28 B; gap chunk — no .debug$F/FPO record) —
// PA-units -> fixed-24 altitude scale, the exact inverse of F24ToPA (wave
// 18 src/F24ToPA.c): pa * 1406 + 500 round, / 1000. FA asm: movsx eax,cx
// (SHORT fastcall arg in ecx) / mov ecx,0x57e (1406 = 2*703) / imul ecx
// (one-operand edx:eax *= 1406) / add eax,0x1f4 / adc edx,0 (+500 = half of
// 1000, round-to-nearest) / mov ecx,0x3e8 / idiv ecx / ret (+census 8b c0
// pad). C-unreachable: CL folds /1000 into a magic-multiply and its multiply
// plans are register-canonical — naked asm escape, F24ToPA's exact family
// (probe b19c_pato byte-exact first try, zero relocs).
int __declspec(naked) __fastcall PAToF24(short x)
{
    __asm {
        movsx   eax, cx
        mov     ecx, 0x57e
        imul    ecx
        add     eax, 0x1f4
        adc     edx, 0
        mov     ecx, 0x3e8
        idiv    ecx
        ret
    }
}