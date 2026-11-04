/* w36B v2: _WRColorPalette@16 rva 0xc52c0 (108 B, gap chunk, no FPO).
 * v2 of the whole-body naked-asm: v1's only byte deltas were the cmp [ebp+14h],1
 * (CL/MASM folded to 83 7d 14 01; FA carries the 7-B 81 7d 14 00 01 00 00)
 * so the imm-16 compare is _emit-spliced verbatim.
 */
void __declspec(naked) __stdcall WRColorPalette(unsigned char *dst,
                                                int n, unsigned char *col,
                                                int mode)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push edi
        mov edi, [ebp+10h]
        mov bl, [edi]
        neg bl
        mov bh, [edi+1]
        neg bh
        mov dl, [edi+2]
        neg dl
        mov edi, [ebp+8]
        mov ecx, [ebp+0Ch]
        _emit 081h
        _emit 07dh
        _emit 014h
        _emit 000h
        _emit 001h
        _emit 000h
        _emit 000h
        je Lflat
        mov dh, [ebp+14h]
        shr dh, 1
Lbl:    mov al, [edi]
        add al, bl
        imul dh
        shl ax, 1
        sub [edi], ah
        mov al, [edi+1]
        add al, bh
        imul dh
        shl ax, 1
        sub [edi+1], ah
        mov al, [edi+2]
        add al, dl
        imul dh
        shl ax, 1
        sub [edi+2], ah
        add edi, 3
        loop Lbl
Lpop:   pop edi
        pop ebx
        pop ebp
        ret 10h
Lflat:  mov [edi], bl
        mov [edi+1], bh
        mov [edi+2], dl
        add edi, 3
        loop Lflat
        jmp Lpop
    }
}