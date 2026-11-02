// @MAPSetSide@4 @ rva 0x21e40 (138816, ? B) — fastcall: byte p[9] =
//   (p[9] & 0x7f) | nationSides[p[9] & 0x7f]. FA keeps the masked byte
//   parked in dl across the two stores; the index is a live zeroed eax.
// EXACT as plain C (survey tier-1 probe v1; naked-asm d41 superseded):
//   unsigned char locals t/u — CL emits the masked byte into a register,
//   stores it twice with the index reuse, and the sib byte-load
//   nationSides[u] falls out of the uchar array type + zero-extended
//   index. v2 (re-read p[9] in the last store) also EXACT; v1 kept for
//   provenance. Maps VERBATIM: [] (nationSides resolves identity).
//
// probes: build/survey/probes/t1_mapset_v1.c (EXACT), t1_mapset_v2.c
//   (EXACT), t1_mapset_v3.c (no) — run: python3 build/survey/hybrid_probe.py
//   build/survey/probes/tier1_re.json
extern unsigned char nationSides[];

void __fastcall MAPSetSide_q(char *p)
{
    unsigned char t = p[9];
    unsigned char u = (unsigned char)(t & 0x7f);
    p[9] = u;
    p[9] = (unsigned char)(u | nationSides[u]);
}