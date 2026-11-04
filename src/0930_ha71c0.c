/* @w30a_a71c0@8 @ rva 0xa71c0, 32 B. FA bytes:
 *   66 8b 12 mov dx,[edx] ; 66 8b 01 mov ax,[ecx] ; 66 3b c2 cmp ax,dx
 *   jbe +6 ; mov eax,-1 ; ret ; mov eax,1 ; adc eax,-1 ; ret
 * Load p2 FIRST so its value lands in dx (FA order), p1 in ax.
 */
int __fastcall w30a_a71c0(unsigned short *p1, unsigned short *p2)
{
    unsigned short b = p2[0];
    unsigned short a = p1[0];
    if (a > b) return -1;
    if (a < b) return 1;
    return 0;
}