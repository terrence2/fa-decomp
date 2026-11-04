/* w32H_0c2810_v6: @Zeromem@8 via inline __asm (one allowed retry). */
void __fastcall Zeromem(void *dst, int n)
{
    __asm {
        mov edi, ecx
        mov ecx, edx
        xor eax, eax
        mov ah, al
        cmp ecx, 0x10
        jbe zsmall
        push ebx
        push ax
        mov ebx, 4
        shl eax, 0x10
        sub ebx, edi
        pop ax
        and ebx, 3
        mov [edi], eax
        sub ecx, ebx
        add edi, ebx
        sub ecx, 0x10
        mov ebx, 0x10
    zloop:
        jle ztail
        mov [edi], eax
        mov [edi+4], eax
        mov [edi+8], eax
        mov [edi+12], eax
        add edi, ebx
        sub ecx, ebx
        jmp zloop
    ztail:
        add ecx, ebx
        rep stosb
        pop ebx
        jmp zpop
    zsmall:
        shr ecx, 1
        rep stos word ptr [edi]
        adc ecx, ecx
        rep stosb
    zpop:
        pop edi
        pop ebx
    }
}
