// _G_SetPalette@16 @ rva 0x955f0 (32 B) — FA asm: mov eax,[esp+0x10] / mov
// ecx,[esp+0xc] / mov edx,[esp+0x8] / push eax / push ecx / push edx stack
// shuffle then call GG_SetPalette@16, bare ret 0x10 (NOT a tail jmp — callee
// is stdcall and cleans its own 16). The `return GG_SetPalette(...)` form
// made CL reproduce that exactly (probe b17c_gsetpalette_v1 byte-exact;
// a plain forward form `GG(...);` without return also fit — v2). _GG_SetPalette@16
// is identity, no maps.
extern int __stdcall GG_SetPalette(int a, int b, int c, int d);

int __stdcall G_SetPalette(int a, int b, int c, int d)
{
    return GG_SetPalette(a, b, c, d);
}