// w43G chunk rva 0xc902c (152 B) = _CopyDB8: CopyDB15-family (wave-41F recipe).
// 4x unrolled TABLE copy with 16-B word transfers (shl bx,2 ; mov ax,[ebx] ; mov [edx],ax),
// pusha/popa band bare (60/61), push ebp frame; params edi/edx/esi/ecx at +8/+c/+10/+14.
// Block schedule: A(+edx,2 / inc esi / sub edx,ecx), B(sub edx,2 / inc esi / add edx,ecx),
// A, B. Tail pad 2e 8b c0. Whole-body naked asm (pusha/movs real, 60/61 + tail _emit, per
// w41F_CopyDB15_v1.c which is EXACT).
void __declspec(naked) w43G_CopyDB8(void)
{
    __asm {
        push ebp
        mov ebp, esp
        _emit 0x60
        mov edi, [ebp+8]
        mov edx, [ebp+0xc]
        mov esi, [ebp+0x10]
        mov ecx, [ebp+0x14]
        push ebx
        push eax
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 2
        add ebx, edi
        mov ax, word ptr [ebx]
        mov [edx], ax
        add ebx, 2
        add edx, ecx
        mov ax, word ptr [ebx]
        mov [edx], ax
        add edx, 2
        inc esi
        sub edx, ecx
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 2
        add ebx, edi
        mov ax, word ptr [ebx]
        mov [edx], ax
        add ebx, 2
        add edx, ecx
        mov ax, word ptr [ebx]
        mov [edx], ax
        sub edx, 2
        inc esi
        add edx, ecx
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 2
        add ebx, edi
        mov ax, word ptr [ebx]
        mov [edx], ax
        add ebx, 2
        add edx, ecx
        mov ax, word ptr [ebx]
        mov [edx], ax
        add edx, 2
        inc esi
        sub edx, ecx
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 2
        add ebx, edi
        mov ax, word ptr [ebx]
        mov [edx], ax
        add ebx, 2
        add edx, ecx
        mov ax, word ptr [ebx]
        mov [edx], ax
        pop eax
        pop ebx
        _emit 0x61
        pop ebp
        ret
        _emit 0x2e
        _emit 0x8b
        _emit 0xc0
    }
}