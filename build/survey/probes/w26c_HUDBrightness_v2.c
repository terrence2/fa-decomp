// @HUDBrightness@4 @ rva 0xa8a0 = 43168, 80 B (fastcall 1 arg -> ecx; FA:
//   cmp cl,1; mov ecx,[g]; sbb eax,eax; and eax,-0x20; add eax,0x10;
//   add ecx,eax; mov [g],ecx; cmp ecx,-0x100; jge L1; mov [g],-0x100;
//   ret; L1: mov [g],ecx; cmp ecx,0x100; jle ret; mov [g],0x100; ret.
//   v2: delta temp declared first (e -> EAX), two sequential
//   passthrough-ternaries (each assignment stores; mid store = ternary-1's
//   TRUE branch).
extern int w26_hudBright; /* map _w26_hudBright=?hudBrightness@@3JA */

void __fastcall w26c_HUDBrightness_q(unsigned char p1)
{
    int e = (p1 < 1) ? -16 : 16;
    w26_hudBright += e;
    w26_hudBright = (w26_hudBright > -256) ? w26_hudBright : -256;
    w26_hudBright = (w26_hudBright > 256) ? 256 : w26_hudBright;
}