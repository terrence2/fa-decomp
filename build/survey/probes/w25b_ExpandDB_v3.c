void __declspec(naked) ExpandDB(char *s, char *d)
{
    __asm {
        push ebp
        mov ebp, esp
        _emit 0x60
        mov eax, [ebp + 8]
        mov edx, [ebp + 0xc]
        _emit 0x66
        _emit 0x51
        push ebx
        _emit 0x66
        _emit 0xb9
        _emit 0x00
        _emit 0x02
expand_loop:
        inc eax
        mov bl, [eax]
        mov bh, bl
        dec eax
        shl ebx, 16
        mov bl, [eax]
        mov bh, bl
        inc eax
        inc eax
        mov [edx], ebx
        add edx, 4
        mov [edx], ebx
        add edx, 4
        _emit 0x66
        _emit 0x49
        _emit 0x75
        _emit 0xe3
        _emit 0x5b
        _emit 0x66
        _emit 0x59
        _emit 0x61
        pop ebp
        ret
    }
}