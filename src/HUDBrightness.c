// @HUDBrightness@4 @ rva 0xa8a0 = 43168, 80 B (fastcall 1 arg -> ecx; FA:
//   cmp cl,1; mov ecx,[g]; sbb eax,eax; and eax,-0x20; add eax,0x10; add
//   ecx,eax; mov [g],ecx; cmp ecx,-0x100; jge; mov [g],-0x100; ret; mov
//   [g],ecx; cmp ecx,0x100; jle; mov [g],0x100; ret; lea pads).
// v3 (EXACT recipe): named e local for the delta (materialises the sbb
//   chain in EAX with the += target in ECX), plain += store, then the two
//   clamps as if/return on the global — CL keeps per-branch stores with
//   the pass-through re-store and range-folds the 2nd clamp on the const
//   path (ret).
extern int w26_hudBright; /* map _w26_hudBright=?hudBrightness@@3JA */

void __fastcall w26c_HUDBrightness_q(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright = w26_hudBright + e;
    if (w26_hudBright < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    if (w26_hudBright > 0x100)
        w26_hudBright = 0x100;
}