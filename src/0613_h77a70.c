extern char g_buf[];
extern unsigned long g_len;

void __declspec(naked) w32f_hintlen(void)
{
    __asm {
        push edi
        _emit 0b9h
        _emit 0ffh
        _emit 0ffh
        _emit 0ffh
        _emit 0ffh
        mov edi, offset g_buf
        sub eax, eax
        repnz scasb
        not ecx
        dec ecx
        pop edi
        mov g_len, ecx
        ret
    }
}
