// ?SetVESABank@@YAGG@Z @ rva 0x69fb0 (16 B) — 66 33 c0 / c3: the ushort
// return is cleared with the 16-bit xor; plain C `return 0` emits exactly
// that (probe w13a_ushort0 w13a_us0a exact).
unsigned short __cdecl SetVESABank(unsigned short bank)
{
    return 0;
}