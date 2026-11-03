/* _GRAPHICAddInvisible@20 @ rva 0x43710 (96 B), stdcall 5 args.
 * FA: eax=a5; push esi; ecx=a2; push -1, a5, a2; al = low byte of a1;
 * eax &= 0xffff00ff (blend = (a5 & 0xffff0000) | a1 & 0xff);
 * push blend; push 0x2b; call $FA$_t_443190 -> obj (0 = fail).
 * if obj: WORD[obj+4] = low word of a4; if (a5) copy 6 B a5 -> obj+0x1c
 * else zero 6 B at obj+0x1c (3 word stores 0x20,0x1e,0x1c).
 * ret 0x14 (5-arg stdcall), returns obj in eax. */
extern int w33h_msg43(int a, unsigned b, int c, int d, int e); /* $FA$_t_443190 */

int __stdcall GRAPHICAddInvisible(int a1, int a2, int a3, int a4, int a5)
{
    int obj;
    obj = w33h_msg43(0x2b, (a5 & 0xffff0000u) | (a1 & 0xffu), a2, a5, -1);
    if (obj) {
        *(unsigned short *)(obj + 4) = (unsigned short)a4;
        if (a5)
            *(unsigned *)(obj + 0x1c) = *(unsigned *)a5,
            *(unsigned short *)(obj + 0x20) = *(unsigned short *)(a5 + 4);
        else
            *(unsigned *)(obj + 0x1c) = 0,
            *(unsigned short *)(obj + 0x20) = 0;
    }
    return obj;
}
