// Wave 46 batch C entry 4: _strcat @ rva 875328 (0xd5b40), 224 B. CRT strcat
// (sibling recipe: src/w29b_strlen_v2.c naked-asm 0x7efefeff strlen; _strcpy
// already forwards into _strcat+0x61). Naked transcription, FPO esp, 2 params.
// dst-scan with aligned dwords + byte-exit lea edi,src[]; src copy loop with
// unaligned byte head and dword body, byte-tail exits store NUL variants.
// No tail pad (16-aligned code end), no relocs (all jmps internal).
void __declspec(naked) strcat_q(void)
{
    __asm {
    Lhead:
        mov  ecx, [esp+0x4]
        push edi
        test ecx, 3
        je   Lscan
    Lb1:
        mov  al, [ecx]
        inc  ecx
        test al, al
        je   Lbyte1
        test ecx, 3
        jne  Lb1
    Lscan:
        mov  eax, [ecx]
        mov  edx, 07efefeffh
        add  edx, eax
        xor  eax, -1
        xor  eax, edx
        add  ecx, 4
        test eax, 081010100h
        je   Lscan
        mov  eax, [ecx-4]
        test al, al
        je   Lr4
        test ah, ah
        je   Lr3
        test eax, 0ff0000h
        je   Lr2
        test eax, 0ff000000h
        je   Lbyte1
        jmp  Lscan
    Lbyte1:
        lea  edi, [ecx-0x1]
        jmp  Lsrc
    Lr2:
        lea  edi, [ecx-0x2]
        jmp  Lsrc
    Lr3:
        lea  edi, [ecx-0x3]
        jmp  Lsrc
    Lr4:
        lea  edi, [ecx-0x4]
    Lsrc:
        mov  ecx, [esp+0xc]
        test ecx, 3
        je   Ldscan
    Lb2:
        mov  dl, [ecx]
        inc  ecx
        test dl, dl
        je   Lc1
        mov  [edi], dl
        inc  edi
        test ecx, 3
        jne  Lb2
        _emit 0xeb          ; jmp +5 past the store block (CL block-reorders
        _emit 0x05          ; this block if left as real asm -- wave-42)
    Ldloop2:
        _emit 0x89          ; mov [edi],edx
        _emit 0x17
        _emit 0x83          ; add edi,4
        _emit 0xc7
        _emit 0x04
    Ldscan:
        mov  edx, 07efefeffh
        mov  eax, [ecx]
        add  edx, eax
        xor  eax, -1
        xor  eax, edx
        mov  edx, [ecx]
        add  ecx, 4
        test eax, 081010100h
        je   Ldloop2
        test dl, dl
        je   Lc1
        test dh, dh
        je   Lc3
        test edx, 0ff0000h
        je   Lc4
        test edx, 0ff000000h
        je   Lc5
        jmp  Ldloop2
    Lc5:
        mov  [edi], edx
        mov  eax, [esp+0x8]
        pop  edi
        ret
    Lc4:
        mov  [edi], dx
        mov  eax, [esp+0x8]
        mov  byte ptr [edi+2], 0
        pop  edi
        ret
    Lc3:
        mov  [edi], dx
        mov  eax, [esp+0x8]
        pop  edi
        ret
    Lc1:
        mov  [edi], dl
        mov  eax, [esp+0x8]
        pop  edi
        ret
    }
}