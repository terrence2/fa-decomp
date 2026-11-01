// ?SetTOD@@YAXGG@Z @ rva 0x69fa0 (16 B) — FA asm: c3 / lea esp,[esp+0] /
// lea esp,[esp+0] / lea esp,[esp+0] (8d a4 24 00 00 00 00): empty cdecl
// ushort,ushort body; the 15-byte tail is census-proven lea filler
// (probes w17b_ushort0 family) auto-appended at fit. No maps.
void __cdecl SetTOD(unsigned short a, unsigned short b)
{
}