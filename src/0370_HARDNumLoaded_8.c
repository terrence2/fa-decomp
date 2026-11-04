/* @HARDNumLoaded@8 @ rva 0x530e0 — plain C (tier-0 re-read).
 * FA: obj = objPtrs[p1&0xffff]; n = *(obj+0x114) + p2*16 + p2; return
 * *(ushort*)(obj + n + 4) & 0x7fff. The decisive lever (v7): the & 0x7fff
 * must live on an unsigned long return — and eax,0x7fff clears bits 15..31,
 * so the ushort load + 32-bit and is faithful; with an int/ushort return CL
 * narrowed to and-ax (66 25 ff 7f) where FA spells the full 25 ff 7f 00 00.
 * No other steering needed; p2*16+p2 stays folded.
 *
 * probes: v1-v6 (no: and-ax narrowing), build/survey/probes/HARDNumLoaded_v7.c
 *   (EXACT) — run: python3 build/survey/hybrid_probe.py
 *   build/survey/probes/tier0_r5.json
 *
 * maps: none
 */
extern unsigned long objPtrs[];
unsigned long __fastcall HARDNumLoaded_m(int p1, int p2)
{
    unsigned long obj, n;
    obj = objPtrs[p1 & 0xffff];
    n = *(unsigned long *)((char *)obj + 0x114) + p2 * 16 + p2;
    return *(unsigned short *)((char *)obj + n + 4) & 0x7fff;
}