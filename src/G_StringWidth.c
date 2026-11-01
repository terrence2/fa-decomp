extern char *cFont;
__declspec(naked) int __fastcall G_StringWidth(char *p)
{
    __asm {
        push ebx
        xor eax, eax
        cmp byte ptr [ecx], al
        je fin
    L:  xor ebx, ebx
        mov edx, dword ptr [cFont]
        mov bl, byte ptr [ecx]
        inc ecx
        mov edx, dword ptr [edx + ebx*4 + 0x404]
        mov bl, byte ptr [ecx]
        inc edx
        add eax, edx
        test bl, bl
        jne L
    fin:
        dec eax
        pop ebx
        ret
    }
}
