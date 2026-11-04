/* w37E candidate 0xdd470 v11: whole-body naked asm (the one allowed inline-asm
   escape hatch). CL 4.2 could not reproduce FA's duplicated latch tests: /O2
   merges the three branch tails and hoists the post-inc load ([eax+1] before
   inc); /O1 keeps the shape but RA flips to push esi + dl-compares. FA chunk is
   67 B, relocation-free, so the body is emitted 1:1. */
void __declspec(naked) __cdecl w37e_dd470na(char *s)
{
    __asm {
        mov     edx, [esp+4]
        push    ebx
        cmp     byte ptr [edx], 0
        je      Ld_exit2
Ld_top:
        mov     al, [edx]
        cmp     al, 0x30
        jl      Ld_semi
        cmp     al, 0x39
        jg      Ld_semi
        sub     al, 0x30
        mov     [edx], al
        inc     edx
        cmp     byte ptr [edx], 0
        jne     Ld_top
        pop     ebx
        ret
Ld_semi:
        cmp     al, 0x3b
        jne     Ld_else
        mov     eax, edx
Ld_del2:
        lea     ecx, [eax+1]
        mov     bl, [ecx]
        mov     [eax], bl
        mov     eax, ecx
        cmp     byte ptr [ecx], 0
        jne     Ld_del2
        cmp     byte ptr [edx], 0
        jne     Ld_top
        pop     ebx
        ret
Ld_else:
        inc     edx
        cmp     byte ptr [edx], 0
        jne     Ld_top
Ld_exit2:
        pop     ebx
        ret
    }
}