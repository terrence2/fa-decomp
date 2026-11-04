/* DoNibble @ rva 0xc5010 (120 B) -- v1 naked asm.
 * Gap chunk with register ABI (al = nibble in, edi = emit cursor in/out);
 * no frame, no relocs, ends plain ret. Emits instruction-prefix bytes 66/a5/a4/47. */
void __declspec(naked) DoNibble(void)
{
    __asm {
        cmp al, 0x0f
        jne LX1
        mov byte ptr [edi], 0xa5
        inc edi
        jmp LB
    LX1:
        mov ah, al
        shr al, 2
        cmp al, 3
        jne LX2
        mov byte ptr [edi], 0x66
        inc edi
        mov byte ptr [edi], 0xa5
        inc edi
        jmp LM
    LX2:
        cmp al, 2
        jne LX3
        mov byte ptr [edi], 0xa4
        inc edi
        mov byte ptr [edi], 0x47
        inc edi
        jmp LM
    LX3:
        cmp al, 1
        jne LX4
        mov byte ptr [edi], 0x47
        inc edi
        mov byte ptr [edi], 0xa4
        inc edi
        jmp LM
    LX4:
        mov byte ptr [edi], 0x47
        inc edi
        mov byte ptr [edi], 0x47
        inc edi
    LM:
        mov al, ah
        and al, 3
        cmp al, 3
        jne LX5
        mov byte ptr [edi], 0x66
        inc edi
        mov byte ptr [edi], 0xa5
        inc edi
        jmp LB
    LX5:
        cmp al, 2
        jne LX6
        mov byte ptr [edi], 0xa4
        inc edi
        mov byte ptr [edi], 0x47
        inc edi
        jmp LB
    LX6:
        cmp al, 1
        jne LX7
        mov byte ptr [edi], 0x47
        inc edi
        mov byte ptr [edi], 0xa4
        inc edi
        jmp LB
    LX7:
        mov byte ptr [edi], 0x47
        inc edi
        mov byte ptr [edi], 0x47
        inc edi
    LB:
        ret
    }
}