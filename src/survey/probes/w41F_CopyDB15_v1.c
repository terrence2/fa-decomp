// w41F _CopyDB15 @ rva 0xc9120 (136 B): 4x unrolled table-copy with a
// pusha/popa save band (60/61 = asm-only, SetFlatColor _emit recipe).
// Body: for each of 15+.. source byte indexes: idx = *p++; row = tab + (idx<<3);
// copy row[0] -> dst[col], row[1] -> dst[col + stride]; dst col advances
// 0/4/2*stride... per FA's own un-scheduled add/sub dance. Full naked asm
// (pusha/popa + the exact FA add/sub scheduling is CL-hostile anyway).


void __declspec(naked) w41F_CopyDB15(void)
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
        shl bx, 3
        add ebx, edi
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add edx, 4
        inc esi
        sub edx, ecx
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 3
        add ebx, edi
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        sub edx, 4
        inc esi
        add edx, ecx
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 3
        add ebx, edi
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add edx, 4
        inc esi
        sub edx, ecx
        xor ebx, ebx
        mov bl, byte ptr [esi]
        shl bx, 3
        add ebx, edi
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        pop eax
        pop ebx
        _emit 0x61
        pop ebp
        ret
    }
}