// @WritePalette@8 @ rva 0x69f80 — mov eax,edx / push 1 / mov esi,3 / sub
//   edx,edx / div esi / push eax / push 0 / push ecx / call _G_SetPalette@16
//   / pop esi / ret (probe v8: unsigned b/3 keeps the mov esi/sub edx/div
//   sequence; stdcall callee cleans, no add esp,4).
extern void __stdcall G_SetPalette_x(int a, int b, int c, int d);

void __fastcall WritePalette(int a, unsigned int b)
{
    G_SetPalette_x(a, 0, b / 3, 1);
}
