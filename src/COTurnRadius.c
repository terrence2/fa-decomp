// _COTurnRadius@0 @ rva 0x77020 (64 B) — heading of _curThing+0x34 >> 8 (sar
//   into esi + 8b c6 copy) scaled by 10433 through the lea chain (x9 / x9
//   [esi re-purposed] / s+x*2 / <<3 / s+x*8 -> ebx), divided by COTurnRate()
//   (call survives the chain: cdq / idiv ecx), clamped to 0x7fff: FA's
//   pre-init min (mov ecx,0x7fff / cmp eax,imm / jg / mov ecx,eax / mov
//   eax,ecx) is a toolchain revision delta — every /O2 /Gy /G5 source form
//   gives either pre-init+reg-cmp (d14b3 CR v3: b9/3b c1/7f/8b c8/8b c1) or
//   imm-cmp+jle+b8 (d14b4 CRc/CRd), never the union; fitobj --patch
//   0x2d,2,3dff7f0000 expands 3b c1 to 3d ff7f0000 (no relocs after 0x2d).
extern long __stdcall COTurnRate(void);
extern char curThing[];
long __stdcall COTurnRadius_q(void)
{
    long s, b, t, q;
    s = *(long *)(curThing + 0x34) >> 8;
    b = s + ((s + 2 * (s * 9) * 9) << 3) * 8;
    t = b / COTurnRate();
    q = 0x7fff;
    if (t <= 0x7fff)
        q = t;
    return q;
}