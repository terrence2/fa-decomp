// _RotatedOffset@20 @ rva 0x11aa0 (48 B) — fixed-point arg shift thunk.
// EXACT as plain C (wave-23 probe): call _RotatedOffsetF24@20 with p2, p3,
// p4 shifted left by the 8-bit fixed-point fraction while p1 and p5 pass
// raw. The naked-asm header claimed CL's shift-in-ecx/raw-in-eax split was
// unsteerable; the plain-C form reproduces FA's plan directly. Ret 0x14
// (stdcall both sides).
// Map: _RotatedOffsetF24Q@20=_RotatedOffsetF24@20.
extern long __stdcall RotatedOffsetF24Q(long a1, long a2, long a3, long a4,
                                        long a5);

long __stdcall RotatedOffset(long p1, long p2, long p3, long p4, long p5)
{
    return RotatedOffsetF24Q(p1, p2 << 8, p3 << 8, p4 << 8, p5);
}