/* @CTDo_exit@0 @ rva 0x64bf0 — plain C (tier-0 re-read).
 * FA: if (serviceTicks[0xec]) return; r = ctdoQuit_(0); then
 * mov cl,[ticks+0xf8]; or cl,r; mov [ticks+0xf8],cl. The decisive lever
 * (v5): the load/or/store triple must read through a volatile-typed lvalue
 * — an expression-instant volatile lets CL fuse (08 05 or [mem],al) like the
 * plain |= spelling does, but a NAMED volatile local materializes FA's real
 * 8a/0a/88 triple. v4's compile failures: the callee returns char.
 *
 * probes: v1-v4 (no / compile fail on void callee), build/survey/probes/
 *   CTDo_exit_v5.c (EXACT) and v6 (no) — run: python3 build/survey/
 *   hybrid_probe.py build/survey/probes/tier0_r5.json
 *
 * maps (unchanged): @ctdoQuit_@4=$FA$_t_463e90
 */
extern char serviceTicks[];
extern char __fastcall ctdoQuit_(int a);
void CTDo_exit_s(void)
{
    char m, r;
    if (*(char *)(serviceTicks + 0xec))
        return;
    r = ctdoQuit_(0);
    m = *(volatile char *)(serviceTicks + 0xf8);
    m = m | r;
    *(volatile char *)(serviceTicks + 0xf8) = m;
}