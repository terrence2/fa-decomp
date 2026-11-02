// fast_asin @ rva 0xc9aeb (36 B, gap chunk, no FPO) — pure register asm:
// |ax| via cwd/xor/sub 16-bit abs, +0x80, index = (ah << 1) zero-extended
// into ebx, fetch sign-corrected word from cos_table+0x202[ebx], negate
// back via the entry cwd sign. ah/bh access and the entry cwd make this
// asm-only. __cdecl (c3).
extern short fastAsinTab[];          /* cos_table + 0x202 */

void __declspec(naked) __cdecl fast_asin_q(void)
{
    __asm {
        cwd
        xor  ax, dx
        sub  ax, dx
        add  ax, 0x80
        mov  bl, ah
        xor  bh, bh
        shl  bx, 1
        movzx ebx, bx
        mov  cx, word ptr fastAsinTab[ebx]
        xor  cx, dx
        sub  cx, dx
        ret
    }
}