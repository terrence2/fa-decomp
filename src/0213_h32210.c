// 0x32210 (32 B) — v2 naked asm: 16-bit seed scramble (Rand(v*2); ax -= v)
extern int Rand2(void);

long __declspec(naked) w30d_rseed16(void)
{
    __asm {
        push esi
        imul cx, cx, 0B6h
        mov si, cx
        lea ecx, [esi*2]
        call Rand2
        sub ax, si
        pop esi
        ret
    }
}