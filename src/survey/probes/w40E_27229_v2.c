/* rva 160297 (0x27229) v2 — flow-shape clamps: FA's low-clamp path
 * rejoins the high clamp (xor eax / jmp end), so spell the two clamps
 * as if-seq on t, not early returns. CL /O2 folds (t/d)*d to an
 * 8d-chain multiply (13 B) — patched to FA's bare 0f af c6. */
int __stdcall w40E_Bound(long base, long rate, short mult)
{
    long t, d;

    d = 0x3e800;
    t = base + mult * rate + 0x1f400;
    t = t / d * d;
    if (t < 0) t = 0;
    if (t > 0xea6000) t = 0xea6000;
    return t;
}