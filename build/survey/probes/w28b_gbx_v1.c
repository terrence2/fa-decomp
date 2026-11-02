/* _G_Box@16 @ 0x95ec0 — v1 */
extern void __stdcall w28b_HL(long a, long b, long c);    /* -> _G_Hline@12 */
extern void __stdcall w28b_VL(long a, long b, long c);    /* -> _G_Vline@12 */

void __stdcall w28b_gbx_f(long x, long y, long w, long h)
{
    long xe = x + w - 1;
    long ye = y + h - 1;
    w28b_HL(x, xe, y);
    w28b_HL(x, xe, ye);
    w28b_VL(x, y, ye);
    w28b_VL(xe, y, ye);
}
