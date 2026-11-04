// w35D_d9900_v1: nameless 43-B chunk @ 0xd9900 (2 stack args, fpo/esp).
// FA: push esi/edi, mov esi,[esp+0x10] (src), test, je exit, mov
// edx,[esp+0xc] (dst), ecx=-1, edi=edx, xor eax,eax (2b c0), repnz scasb,
// not ecx, push ecx (len+1), push edx (dst), edx+=esi, push edx (dst+len),
// call memmove, add esp,0xc, pop edi/esi, ret, pad 4xcc.
extern void *memmove(void *, const void *, unsigned long);

void __declspec(naked) w35d_d9900(void)
{
    __asm {
        push esi
        push edi
        mov esi, dword ptr [esp+0x10]
        test esi, esi
        je  L_end
        mov edx, dword ptr [esp+0xc]
        mov ecx, -1
        mov edi, edx
        sub eax, eax
        repnz scasb
        not ecx
        push ecx
        push edx
        add edx, esi
        push edx
        call memmove
        add esp, 0ch
        L_end:
        pop edi
        pop esi
        ret
    }
}