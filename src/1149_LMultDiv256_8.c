// @LMultDiv256@8 @ rva 0xc299c (12 B) — fixed-point multiply then /256:
//   mov eax, ecx        ; p1
//   movsx edx, dx       ; sign-extend short p2 in place
//   imul edx            ; 64-bit product edx:eax = p1 * (long)p2
//   shrd eax, edx, 8    ; >> 8, low dword (floor division by 256)
//   ret
// C-unreachable: CL 4.2's 32x32 __int64-multiply plan is register-canonical
// (always mov eax, edx / imul ecx for fastcall args, regardless of
// expression order — w14c_m4-vs-f5).  No short-param __int64 form stays
// inline either (w14c_m7-m9 collapse into an LL-divide helper call).
// Naked asm escape, w14d round: exact.
int __declspec(naked) __fastcall LMultDiv256(int a, int b)
{
    __asm
    {
        mov eax, ecx
        movsx edx, dx
        imul edx
        shrd eax, edx, 8
        ret
    }
}
