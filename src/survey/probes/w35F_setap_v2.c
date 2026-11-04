/* w35F @SetAutopilot@8 @ 0x16110 — v2 (two-if bit-set shape, clr tests 0x1000)
 * FA: push ebx; test cl,cl; mov bl,dl; je D; a1 <CTf>; test ah,0x10;
 * jne C(second-if); push 0; call WPSetupCurrent; a1; mov ecx,ebx;
 * or eax,0x1000; a3; call T; jmp E; C: test cl,cl; jne E; D: a1;
 * test ah,0x10; je F(thread); and eax,~0x1000; a3; call CancelCmdBuf;
 * E: a1; test ah,0x10; jne end; and eax,~0x2000; a3; pop ebx; ret */
extern char curThing[];                  /* bare public _curThing */
extern void __stdcall w35f_wpsetup(int); /* -> _WPSetupCurrent@4 */
extern void __stdcall w35f_cancelq(void);/* -> _CancelCmdBuf@0 */
extern void __fastcall w35f_t16(unsigned char); /* -> $FA$_t_416180 */

void __fastcall w35f_setap(unsigned char on, unsigned char x)
{
    if (on) {
        if (!(*(unsigned long *)(curThing + 0x16f) & 0x1000)) {
            w35f_wpsetup(0);
            *(unsigned long *)(curThing + 0x16f) |= 0x1000;
            w35f_t16(x);
            goto clr;
        }
        if (on)
            goto clr;
    }
    if (*(unsigned long *)(curThing + 0x16f) & 0x1000) {
        *(unsigned long *)(curThing + 0x16f) &= ~0x1000;
        w35f_cancelq();
    }
clr:
    if (!(*(unsigned long *)(curThing + 0x16f) & 0x1000))
        *(unsigned long *)(curThing + 0x16f) &= ~0x2000;
}