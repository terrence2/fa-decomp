// w29b D: _WRReddenPalette@12 @ rva 0xc5278 (72 B: 69 code + 2e8bc0*1 tail).
// stdcall(3). FA body reuses ebp as the scale register (0x100-b) after the
// frame prolog, 16-bit mixed imul/mul with ah-byte stores, and a `loop`
// countdown — asm-artifact register plan, naked asm verbatim.
void __declspec(naked) __stdcall WRReddenPal_q(unsigned char *p, int count, int b)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push edi
        mov edi, [ebp+8]
        mov ecx, [ebp+0xc]
        mov ebx, [ebp+0x10]
        mov ebp, 0x100
        sub ebp, ebx
        neg ebx
    Lloop:
        movzx ax, byte ptr [edi]
        sub ax, 0x3f
        imul bx
        add byte ptr [edi], ah
        movzx ax, byte ptr [edi+1]
        mul bp
        mov byte ptr [edi+1], ah
        movzx ax, byte ptr [edi+2]
        mul bp
        mov byte ptr [edi+2], ah
        add edi, 3
        loop Lloop
        pop edi
        pop ebx
        pop ebp
        ret 0xc
    }
}