// ?SetVESATop@@YAXGG@Z @ rva 0x69fc0 (16 B) — FA asm: c3 / lea esp,[esp+0] x2
// / lea esp,[esp+0](8d a4 24 ..): empty cdecl ushort,ushort body; 15-byte
// tail is census-proven lea filler auto-appended at fit. Sibling of
// wave-13 SetVESABank (ushort-arg no-op family). No maps.
void __cdecl SetVESATop(unsigned short a, unsigned short b)
{
}