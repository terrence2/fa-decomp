// _WRWhitenPalette@12 @ rva 0xc521c (92 B = 90 code + 2 pad "8bc0") --
// FA asm: stdcall, 3 args [ebp+8 = palette ptr, +0x0c = count, +0x10
// = step].  Per-RGB-byte: ax = p[i]; ax -= 0x3f; imul bx (bx = arg-0x100
// negated, i.e. negative step); p[i] += ah.  Unrolled x3 then add edi,3
// / loop (ecx countdown).  If step == +0x100: edx=ecx; ecx <<= 1;
// ecx += edx (ecx = 3*count); mov al,0x3f; rep stosb; jmp epilog.
// 16-bit ah/bx register plan with a one-operand imul and MASM `loop` --
// naked-asm escape.
__declspec(naked) void __stdcall WRWhitenPalette(char* p, unsigned n,
                                                 int step)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push edi
        mov edi, [ebp+8]
        mov ecx, [ebp+0Ch]
        mov ebx, [ebp+10h]
        cmp ebx, 100h
        je Lfill
        neg ebx
    Lloop:
        movzx ax, byte ptr [edi]
        sub ax, 3Fh
        imul bx
        add [edi], ah
        movzx ax, byte ptr [edi+1]
        sub ax, 3Fh
        imul bx
        add [edi+1], ah
        movzx ax, byte ptr [edi+2]
        sub ax, 3Fh
        imul bx
        add [edi+2], ah
        add edi, 3
        loop Lloop
    Lfill:
        mov edx, ecx
        shl ecx, 1
        add ecx, edx
        mov al, 3Fh
        rep stosb
        jmp Lepil
    Lepil:
        pop edi
        pop ebx
        pop ebp
        ret 0Ch
    }
}