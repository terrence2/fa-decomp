// _DrawLight @ rva 0x88870 (64 B: 49 code + lea-pad) — 3D light renderer
// step: call the 0x486290 preamble (unanchored gap chunk), load the light
// struct arg then push its three fields SHARING the dirty-upper-bits plan
// (dx word → full edx, al byte → full eax, cx word → ecx; push eax/edx/ecx
// AFTER the test byte [ecx+1],0x80 which reorders past the mov cx load),
// branch on the flag bit, call the wide (bit set → 0x4888b0) or narrow
// (0x488810) light drawer, and tail-jmp the shared draw tail 0x4862a0
// with the 3 args still on the stack. All four targets are UNNAMED gap
// chunks → $FA$_t_ anchors. Reg widths/stale-upper pushes/push-after-test
// are asm-only; naked asm, probe w16b_10 exact.
extern void tDrawLight1(void);      /* $FA$_t_486290 */
extern void tDrawLight2(void);      /* $FA$_t_4888b0 */
extern void tDrawLight3(void);      /* $FA$_t_488810 */
extern void tDrawLightTail(void);   /* $FA$_t_4862a0 */

void __declspec(naked) DrawLight(void)
{
    __asm {
        call tDrawLight1
        mov  ecx, dword ptr [esp+4]
        mov  dx, word ptr [ecx+0xc]
        mov  al, byte ptr [ecx+0x16]
        test byte ptr [ecx+1], 0x80
        mov  cx, word ptr [ecx+0xa]
        push eax
        push edx
        push ecx
        je   Ldl1
        call tDrawLight2
        jmp  tDrawLightTail
Ldl1:
        call tDrawLight3
        jmp  tDrawLightTail
    }
}