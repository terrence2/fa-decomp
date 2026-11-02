/* @w30a_a71c0@8 @ rva 0xa71c0 (dec 684480), 32 B. FA bytes:
 *   66 8b 12    mov dx,[edx]
 *   66 8b 01    mov ax,[ecx]
 *   66 3b c2    cmp ax,dx
 *   76 06       jbe +6
 *   b8 ffff  mov eax,-1 ; ret
 *   b8 01..  mov eax,1
 *   83 d0 ff   adc eax,-1   (1 + CF - 1 = CF = ax<dx unsigned)
 *   c3          ret
 * 3-way unsigned uword compare: a<b -> 1, a==b -> 0, a>b -> -1.
 * Used as function pointer (abs ref at 0x4a694b in T_Make@12).
 */
int __fastcall w30a_a71c0(unsigned short *p1, unsigned short *p2)
{
    unsigned short a = p1[0];
    unsigned short b = p2[0];
    if (a > b) return -1;
    if (a < b) return 1;
    return 0;
}