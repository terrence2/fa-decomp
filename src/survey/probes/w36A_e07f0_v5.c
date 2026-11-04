// w36A_e07f0_v5: naked-asm escape (the one allowed retry). Plain-C
// v2 shape (do-while countdown, pre-dec test) is structurally right at
// both /G4 and /G5 but CL's reg allocation + load scheduling diverge
// (string in ecx/edi; FA keeps string only in edi and preserves count
// in eax). The 44-B code spelled verbatim (Llen falls through into the
// pop/pop/ret epilogue like FA's 0x4d8125 -> 0x4d8129); no externs,
// no relocs, no tail.

unsigned long __declspec(naked) __cdecl strncnt2(void)
{
    __asm {
        mov     eax, dword ptr [esp+8]
        push    esi
        push    edi
        test    eax, eax
        mov     edi, dword ptr [esp+0xc]
        lea     ecx, [eax-1]
        mov     edx, edi
        je      Llatch
Ltop:   cmp     byte ptr [edx], 0
        je      Llen
        inc     edx
        mov     esi, ecx
        dec     ecx
        test    esi, esi
        jne     Ltop
Llatch: cmp     byte ptr [edx], 0
        jne     Lret
Llen:   sub     edx, edi
        mov     eax, edx
Lret:   pop     edi
        pop     esi
        ret
    }
}