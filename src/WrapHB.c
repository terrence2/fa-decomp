// @WrapHB@4 @ rva 0x757c0 (44 B) — heading range wrap: t = v - 0xb400 with the
//   deref pinned in edx (mov edx,[ecx]) and the test in eax; plain C gives the
//   opposite allocation (mov eax,[ecx] + 6-byte sub/add forms, d138, 43 B).
//   Naked asm reproduces FA's three rets and the b0 01/89 11 order in the
//   second block (probe d145).
__declspec(naked) char __fastcall WrapHB_q(int *p)
{
    __asm {
        mov  edx, dword ptr [ecx]
        lea  eax, [edx-0xb400]
        test eax, eax
        jle  short whb1
        sub  eax, 0xb400
        mov  dword ptr [ecx], eax
        mov  al, 1
        ret
    whb1:
        add  edx, 0xb400
        jns  short whb2
        add  edx, 0xb400
        mov  al, 1
        mov  dword ptr [ecx], edx
        ret
    whb2:
        xor  al, al
        ret
    }
}
