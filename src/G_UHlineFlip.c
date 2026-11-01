// _G_UHlineFlip@12 @ rva 0x966e0 (48 B) — G hline family (wave-17
//   G_PolygonFlip/G_UPointFlip twins): FA asm: a1 <_cb> (clipbox pointer's
//   value) / mov edx,[esp+0xc] (x2) / mov ecx,[eax+6] (cb mirror width at
//   +6) / mov eax,[esp+8] (y) / sub ecx,edx / mov edx,[esp+4] (x1) /
//   dec ecx / push ecx / push eax / push edx / call _G_UHline@12 / ret 0xc
//   — mirrors the hline horizontally against the cb rectangle, stdcall
//   right-to-left pushes (a3' first). Plain C exact (probe b19c_uhf_a/b
//   identical; tail = census leal-leal).
extern char *cb;
extern void __stdcall G_UHline(long x1, long y, long x2);

void __stdcall G_UHlineFlip(long x1, long y, long x2)
{
    G_UHline(x1, y, *(long *)((char *)cb + 6) - x2 - 1);
}