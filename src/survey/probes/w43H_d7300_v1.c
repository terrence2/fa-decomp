// __isctype @ rva 0xd7300 (145 B; FPO locals 2 B, params 2, regs 2,
// prolog 0xb).  cdecl (int c, unsigned long mask).  Fast path:
// (unsigned)(c+1) <= 0x100 -> _pctype[c] & mask (xor eax / 66 8b 04 4a).
// Slow path: hi = c>>8 byte (mov dl,ch / mov bl,dl); leadbyte test
// testb 0x80, [__pctype + hi*2 + 1]; kind 2 arm writes blk[2]=hi,
// blk[4]=0, blk[3]=c-low; kind 1 arm blk[2]=c-low, blk[3]=0; blk =
// &local+2 (7-B local, 8-B frame, saved ebx); 6-arg cdecl call
// (1, &c, kind, blk, 0, 0) to stub t000e6 gap chunk VA 0x4dc9b0
// (caller add 0x18); result: 0 or [*blk dword & 0xffff & mask].
extern unsigned short *w43H_pct; /* =_w43H_pct=__pctype */
extern long __cdecl w43H_ide6(int x, void *pc, int kind, void *blk, int z1, int z2); /* =_w43H_ide6=$FA$_t_4dc9b0 */

int __cdecl w43H_isctype2(int c, unsigned long mask)
{
    unsigned char blk[7];
    unsigned char hi;
    unsigned long r;
    r = 0;
    if ((unsigned long)(c + 1) > 0x100) {
        unsigned char hi = (unsigned char)(c >> 8);
        if (*(unsigned char *)((unsigned char *)w43H_pct + hi * 2 + 1) & 0x80) {
            blk[4] = hi;
            blk[6] = 0;
            blk[5] = (unsigned char)c;
            r = w43H_ide6(1, &c, 2, blk + 2, 0, 0);
        } else {
            blk[4] = (unsigned char)c;
            blk[5] = 0;
            r = w43H_ide6(1, &c, 1, blk + 2, 0, 0);
        }
        if (r == 0)
            return 0;
        return *(unsigned long *)(blk + 2) & 0xffff & mask;
    }
    return *(w43H_pct + c) & mask;
}