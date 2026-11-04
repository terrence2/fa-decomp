/* w45A_aulldiv_v1 - rva 0xdc700 __aulldiv (112 B CRT 64-bit unsigned divide, 2 rel32 callers) */
/* naked transcription; C ident _aulldiv -> obj symbol __aulldiv; 8 cc census pad emitted after ret */
void __declspec(naked) _aulldiv(void)
{
    __asm {
        push    ebx
        push    esi
        mov     eax, [esp+0x18]
        or      eax, eax
        jne     Lbig
        mov     ecx, [esp+0x14]
        mov     eax, [esp+0x10]
        xor     edx, edx
        div     ecx
        mov     ebx, eax
        mov     eax, [esp+0xc]
        div     ecx
        mov     edx, ebx
        jmp     Lret
Lbig:   mov     ecx, eax
        mov     ebx, [esp+0x14]
        mov     edx, [esp+0x10]
        mov     eax, [esp+0xc]
Lnorm:  shr     ecx, 1
        rcr     ebx, 1
        shr     edx, 1
        rcr     eax, 1
        or      ecx, ecx
        jne     Lnorm
        div     ebx
        mov     esi, eax
        mul     dword ptr [esp+0x18]
        mov     ecx, eax
        mov     eax, [esp+0x14]
        mul     esi
        add     edx, ecx
        jb      Ladj
        cmp     edx, [esp+0x10]
        ja      Ladj
        jb      Ldone
        cmp     eax, [esp+0xc]
        jbe     Ldone
Ladj:   dec     esi
Ldone:  xor     edx, edx
        mov     eax, esi
Lret:   pop     esi
        pop     ebx
        ret     0x10
        _emit   0xcc
        _emit   0xcc
        _emit   0xcc
        _emit   0xcc
        _emit   0xcc
        _emit   0xcc
        _emit   0xcc
        _emit   0xcc
    }
}