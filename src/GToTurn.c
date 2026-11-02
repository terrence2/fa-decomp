/* @GToTurn@8 @ rva 0x75970 — plain C (tier-0 re-read).
 * FA: b = max(b,0x7d); r = (short)a*2500/(short)b; clamped to
 * [-10240,10240] with the LOW clamp as an early pop-ret and the HIGH clamp
 * falling through to the shared pop-ret. v5's lever: the high clamp must
 * fall through (if (r > 10240) r = 10240; return r;) — v3's early
 * `return 10240` and v4's ternary both made CL save r to ecx (8b c8) before
 * the clamp branch, which FA does not do.
 *
 * probes: v1-v4 (no), build/survey/probes/GToTurn_v5.c (EXACT)
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/tier0_r6.json
 *
 * maps: none
 */
int __fastcall GToTurn_m(int a, int b)
{
    int r;
    if (b < 0x7d)
        b = 0x7d;
    r = (short)a * 2500 / (short)b;
    if (r < -10240)
        return -10240;
    if (r > 10240)
        r = 10240;
    return r;
}