/* $FA$_t_464fa0 @ rva 0x64fa0 (dec 413600), 32 B. FA bytes:
 *   call $FA$_t_464c90
 *   cmp eax,0xf ; jle +6 ; mov eax,0xf ; ret
 *   xor ecx,ecx ; test eax,eax ; setl cl ; dec ecx ; and ecx,eax
 *   mov eax,ecx ; ret
 * Clamp g() to [0,15]: >15 early-return then the classic VC
 * xor/setl/dec/and ternary for v<0?0:v. Plain ret -> cdecl(void).
 */
extern int __cdecl w30a_c90(void);   /* =$FA$_t_464c90 */

int __cdecl w30a_64fa0(void)
{
    int v = w30a_c90();
    if (v > 15) return 15;
    return v < 0 ? 0 : v;
}