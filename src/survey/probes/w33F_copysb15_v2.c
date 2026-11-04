// _CopySB15 @ rva 0xc90c4 (92 B = 89 code + 3 pad "2e8bc0") -- naked-asm
// escape (v1 without naked grew CL's own prolog/reg-saves/epilog +7 B:
// CL inserted its pushes and a 5f 5e 5b tail around the asm block).
void __declspec(naked) CopySB15(void)
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