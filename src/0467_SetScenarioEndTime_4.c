/* @SetScenarioEndTime@4 @ rva 0x63800 — plain C (tier-0 re-read).
 * FA: mov cx,[currentTime]; add cx,param; cmp [endScenarioTime],cx?? — the
 * 66 39/jbe guard: v = a + currentTime; if (endScenarioTime > v)
 * endScenarioTime = v. Two levers, both from v4/v7's split: (1) the externs
 * must be scalar unsigned short so CL emits FA's 66 03 0d add cx,[mem]
 * (pointer-cast expressions *(unsigned short *)currentTime change the add to
 * an a1-load+add-reg — v6 regression); (2) guard polarity `end > v` gives
 * FA's 7e jbe.
 *
 * probes: v1-v5 (no / reg-plan), build/survey/probes/SetScenarioEndTime_v6.c
 *   (no: a1-form add), _v7.c (EXACT) — run: python3 build/survey/
 *   hybrid_probe.py build/survey/probes/tier0_r5.json
 *
 * maps: none
 */
extern unsigned short currentTime;
extern unsigned short endScenarioTime;

void __fastcall SetScenarioEndTime_m(unsigned short a)
{
    unsigned short v = a + currentTime;
    if (endScenarioTime > v)
        endScenarioTime = v;
}