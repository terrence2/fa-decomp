// @WrapP@4 @ rva 0x757f0 (44 B) — pitch range wrap, WrapHB at 0x5a00
//   (probe d146).
__declspec(naked) char __fastcall WrapP_q(int *p)
{
    __asm {
        mov  edx, dword ptr [ecx]
        lea  eax, [edx-0x5a00]
        test eax, eax
        jle  short wp1
        sub  eax, 0x5a00
        mov  dword ptr [ecx], eax
        mov  al, 1
        ret
    wp1:
        add  edx, 0x5a00
        jns  short wp2
        add  edx, 0x5a00
        mov  al, 1
        mov  dword ptr [ecx], edx
        ret
    wp2:
        xor  al, al
        ret
    }
}
