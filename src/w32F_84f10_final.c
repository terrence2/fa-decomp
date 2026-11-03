void __declspec(naked) __fastcall w32f_extdot(char *s)
{
    __asm {
        push ebx
        mov edx, ecx
        push edi
        _emit 0b9h
        _emit 0ffh
        _emit 0ffh
        _emit 0ffh
        _emit 0ffh
        mov edi, edx
        sub eax, eax
        repnz scasb
        not ecx
        mov byte ptr [edx+ecx], 0
        mov al, byte ptr [edx+ecx-2]
        mov byte ptr [edx+ecx-1], al
        mov bl, byte ptr [edx+ecx-3]
        mov byte ptr [edx+ecx-2], bl
        dec ecx
        pop edi
        pop ebx
        mov byte ptr [edx+ecx-2], '.'
        ret
    }
}
