/* @G_SetHShake@8 @ rva 868176 — plain C (tier-0 re-read).
 * FA's shape: early return when (hShakeTicks>0 && hHzMod<hz); the
 * or-0x10 refresh path when (hShakeTicks>0 && hHzMod==hz); else start a new
 * shake (hHzMod=hz, hShakeTicks=amp/4). The two shared guards must be spelled
 * as separate ifs — v1's single combined guard let CL merge them into one
 * test-and-branch pair that FA spells as two.
 * (v2's or-path reads the global directly, no t reuse in the store.)
 *
 * probes: build/survey/probes/G_SetHShake_v1.c (no), _v2.c (EXACT)
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/tier0_r3.json
 *
 * maps: none (globals hShakeTicks/hHzMod resolve from their own stubs)
 */
extern long hShakeTicks;
extern long hHzMod;

void __fastcall G_SetHShake_j(int hz, int amp)
{
    if (hShakeTicks > 0 && hHzMod < hz)
        return;
    if (hShakeTicks > 0 && hHzMod == hz) {
        hShakeTicks = hShakeTicks | 0x10;
        return;
    }
    hHzMod = hz;
    hShakeTicks = amp / 4;
}