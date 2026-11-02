/* $FA$_t_464fa0 @ rva 0x64fa0, 32 B. FA bytes:
 *   call $FA$_t_464c90
 *   cmp eax,0xf ; jle +6 ; mov eax,0xf ; ret
 *   xor ecx,ecx ; test eax,eax ; setl cl ; dec ecx ; and ecx,eax
 *   mov eax,ecx ; ret
 * Mask-trick steering: stage the (v<0) bool into a local, dec, and.
 */
extern int __cdecl w30a_c90(void);   /* =$FA$_t_464c90 */

int __cdecl w30a_64fa0(void)
{
    int v = w30a_c90();
    int m;
    if (v > 15) return 15;
    m = (v < 0);
    m = m - 1;
    m = m & v;
    return m;
}