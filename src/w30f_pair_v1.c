/* w30f pair-chain @ rva 0x2220b (dec 139787), 37 B, gap?? (has FPO, 0 locals)
 * FA:
 *   85 d2              test edx,edx
 *   74 10              je +0x10
 *   89 91 e4 00 00 00  mov [ecx+0xe4],edx
 *   83 c2 44           add edx,0x44
 *   89 91 e8 00 00 00  mov [ecx+0xe8],edx
 *   c3                 ret
 *   33 c0              xor eax,eax
 *   89 81 e8 00 00 00  mov [ecx+0xe8],eax
 *   89 81 e4 00 00 00  mov [ecx+0xe4],eax
 *   c3                 ret
 *   8b ff              (2B pad)
 * fastcall: this=ecx, h=edx. b = h + 0x44.
 */
struct W30fPair {
    int pad[57]; /* 0xe4 */
    int a;
    int b;
};

void __fastcall w30f_pair_v1(struct W30fPair* s, struct W30fPair* h)
{
    if (h) {
        s->a = (int)h;
        s->b = (int)h + 0x44;
    } else {
        s->b = 0;
        s->a = 0;
    }
}