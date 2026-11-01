// @LFDiv@8 @ rva 0xc29b4 (9 B code + 3 B 2e8bc0 pad) — fixed-point divide
// beside @LMultDiv256@8/@LFMult@8:  edx:ecx = (hi:lo) 16.16 pair; quotient
// eax = ((long)lo << 16 sign-extended) / hi.
//   mov eax,ecx / shl eax,16 / xchg edx,ecx / sar edx,16 / idiv ecx / ret
// Naked asm (LMultDiv256 family).  MASM must see "xchg edx, ecx" to emit
// FA's 87 d1 — "xchg ecx, edx" canonicalizes to 87 ca (w16c_3 round 1).
int __declspec(naked) __fastcall LFDiv(int lo, int hi)
{
    __asm
    {
        mov eax, ecx
        shl eax, 10h
        xchg edx, ecx
        sar edx, 10h
        idiv ecx
        ret
    }
}