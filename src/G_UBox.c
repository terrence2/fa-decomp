/* _G_UBox@16 @ 0x95e70 — v1 */
extern void __stdcall w28b_UH(long a, long b, long c);    /* -> _G_UHline@12 */
extern void __stdcall w28b_UV(long a, long b, long c);    /* -> _G_UVline@12 */

void __stdcall w28b_gub_f(long x, long y, long w, long h)
{
    long xe = x + w - 1;
    long ye = y + h - 1;
    w28b_UH(x, xe, y);
    w28b_UH(x, xe, ye);
    w28b_UV(x, y, ye);
    w28b_UV(xe, y, ye);
}
