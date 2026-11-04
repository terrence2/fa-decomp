// w44G @ 0x43c030 (rva 0x3c030, 96 B, unnamed, fastcall (ecx=intf*)).
// ifm visibility gate: p = objPtrs[ecx & 0xffff]; *(long*)(p+1) flag
// (unaligned dword load), nested test chains against ?ifmShow@@3GA,
// tail: return (byte at p) != 6. Unaligned loads + p-in-ecx + test-mem-imm
// forms = naked whole-body transcription. DIR32 sites 0a/27/39/4a.
extern unsigned char w44G_op[];      /* _objPtrs @0x54ad98 */
extern unsigned char w44G_ifs[];     /* ?ifmShow@@3GA @0x4f038c */
__declspec(naked) void w44G_3c030_q(void)
{
    __asm {
        push ebx
        and ecx, 0xffff
        mov ecx, DWORD PTR w44G_op[ecx*4]
        mov edx, DWORD PTR [ecx+1]
        test dl, 1
        jnz L1
        xor al, al
        pop ebx
        ret
    L1:
        mov eax, DWORD PTR [ecx+5]
        mov ebx, DWORD PTR [eax+9]
        test bh, 0x80
        je L2
        test BYTE PTR w44G_ifs, 0x04
        jnz Lc
        xor al, al
        pop ebx
        ret
    L2:
        mov ax, WORD PTR [eax+0xd]
        test ax, WORD PTR w44G_ifs
        jnz Lc
        xor al, al
        pop ebx
        ret
    Lc:
        test dl, 0x10
        jnz Lf
        test BYTE PTR w44G_ifs, 0x20
        je Lf
        xor al, al
        pop ebx
        ret
    Lf:
        mov al, BYTE PTR [ecx]
        pop ebx
        cmp al, 6
        setne al
        ret
        _emit 0x8b
        _emit 0xff
    }
}