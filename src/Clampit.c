// clampit_ @ rva 0xc9391 (27 B, gap chunk; tail 2e 8b c0 = census pad
// filler inside the chunk span) — register-contract 16-bit clamp: cx in,
// cx out, no stack args or caller known (param never loaded from stack —
// the calling convention itself is asm-side). cmp cx,0xff/jg, cmp cx,0/jl,
// three mid-function rets (fall-through = cx unchanged). Naked asm; the
// trailing 2e8bc0 pad is copied by fitobj's census vocabulary, not emitted.
void __declspec(naked) clampit_(void)
{
    __asm {
        cmp  cx, 0xff
        jg   Lhigh
        cmp  cx, 0
        jl   Llow
        ret
Lhigh:
        mov  cx, 0xff
        ret
Llow:
        mov  cx, 0
        ret
    }
}