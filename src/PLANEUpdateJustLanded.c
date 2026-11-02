/* @PLANEUpdateJustLanded@8 @ rva 0x9dd60 — plain C (tier-0 re-read, v1 EXACT).
 * FA: two independent ifs; params are unsigned chars (8-bit tests, 8b-free
 * body); the dword flag updates go through the _curThingFlagQ TO-addend map
 * (_curThing+0x16f) exactly as the stub did.
 * census said nothing here is masked — the chunk was simply never probed.
 *
 * probes: build/survey/probes/PLANE_Update_v1.c (EXACT)
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/tier0_r3.json
 *
 * maps: _curThingFlagQ=_curThing+0x16f (unchanged)
 */
extern char curThingFlagQ[];

void __fastcall PLANEUpdateJustLanded_i(unsigned char a, unsigned char b)
{
    if (a == 0 && b != 0)
        *(unsigned long *)curThingFlagQ |= 0x04000000;
    if (b == 0)
        *(unsigned long *)curThingFlagQ &= 0xfbffffff;
}