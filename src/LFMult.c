// @LFMult@8 @ rva 0xc29a8 (12 B) — 32x32 multiply, take words 2-3:
//   mov eax, ecx        ; p1
//   imul edx            ; edx:eax = p1 * p2
//   shrd eax, edx, 0x10 ; >> 16 (convert 32x32 product to 32x16)
//   ret
// Same C-unreachable register plan as LMultDiv256 (CL always plans
// mov eax, edx / imul ecx for fastcall params — w14c_f1-f6).  Naked asm.
int __declspec(naked) __fastcall LFMult(int a, int b)
{
    __asm
    {
        mov eax, ecx
        imul edx
        shrd eax, edx, 16
        ret
    }
}
