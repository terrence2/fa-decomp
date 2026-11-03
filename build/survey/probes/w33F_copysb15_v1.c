// _CopySB15 @ rva 0xc90c4 (92 B = 89 code + 3 pad "2e8bc0") -- FA asm:
//   push ebp / mov ebp,esp / pushad / read 3 args [ebp+8,+0x0c,+0x10] into
//   ebx (src), edx (dst), ecx (stride) / push eax / 8 unrolled dword copies;
//   dst stride after copy N: N odd -> +4, N even -> +4+ecx (dst walks
//   8 dwords forward, +cx every other dword) / pop eax / popad / pop ebp /
//   ret / cs-mov eax,eax pad.
// Naked-asm escape: FA's pushad/popad register-save band plus the raw
// [ebp+N] arg reads are patch-equal to what CL would emit around a C body.
void CopySB15(void)
{
    __asm {
        push ebp
        mov ebp, esp
        pushad
        mov ebx, [ebp+8]
        mov edx, [ebp+0Ch]
        mov ecx, [ebp+10h]
        push eax
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, 4
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, 4
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, 4
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, 4
        mov eax, [ebx]
        mov [edx], eax
        pop eax
        popad
        pop ebp
        ret
    }
}