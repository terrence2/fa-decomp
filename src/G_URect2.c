// _G_URect2@16 @ rva 0x95e40 (48 B) — FA asm (stdcall, FPO frame): byte-twin
//   of _G_Rect2@16 tail-calling _G_URect@16 with the same two sub/inc
//   width-height conversions from the (x,y,x2,y2) inclusive-corner pair.
//   Plain C exact (probe build/w4probe/b20b_gur2_v1.obj — exact).
extern void __stdcall G_URect(long x, long y, long w, long h);

void __stdcall G_URect2(long x, long y, long x2, long y2)
{
    G_URect(x, y, x2 - x + 1, y2 - y + 1);
}