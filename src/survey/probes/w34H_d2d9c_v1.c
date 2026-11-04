// __compute_viewer_dot_product @ rva 0xd2d9c (76 B, frameless, no FPO).
// Register-ABI helper: the two pointer pseudoparams arrive in edi (dst vec,
// words) and ebx (base vec) and are passed through imul to edx:eax pairs --
// C cannot express edi/ebx-arg reads -> the one allowed naked-asm escape.
// abs moffs viewer_x/y/z ride CL's own asm-reloc HIGHLOWs (payload 0):
// FA imm 0x513bce/d2/d6 == symVA exactly.
extern int viewer_x;
extern int viewer_y;
extern int viewer_z;

void __declspec(naked) _compute_viewer_dot_product(void)
{
    __asm {
        push esi
        mov ax, word ptr [edi]
        shl eax, 10h
        sub eax, dword ptr [viewer_x]
        movsx ecx, word ptr [ebx]
        sar ecx, 1
        imul ecx
        mov ebp, eax
        mov esi, edx
        mov ax, word ptr [edi+2]
        shl eax, 10h
        sub eax, dword ptr [viewer_y]
        movsx ecx, word ptr [ebx+2]
        sar ecx, 1
        imul ecx
        add ebp, eax
        adc esi, edx
        mov ax, word ptr [edi+4]
        shl eax, 10h
        sub eax, dword ptr [viewer_z]
        movsx ecx, word ptr [ebx+4]
        sar ecx, 1
        imul ecx
        add eax, ebp
        adc edx, esi
        pop esi
        ret
    }
}