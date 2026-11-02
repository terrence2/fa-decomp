/* @G_GetPoint@8 @ rva 0x95880 — patch-hybrid (tier-0/Tier-3): plain C + ONE
 * same-length-neutral 7 B patch. Return value: *(char)(obj->f2 * j +
 * obj->f10 + i).
 *
 * patch 0xc: CL folds mov edx,[eax+0xa]; add esi,edx into the mem-operand
 * add esi,[eax+0xa] (03 70 0a) when the base reg dies at the use — a hard
 * CL peephole (10 C spellings incl. volatile named locals all fold or
 * hoist). Patch replaces CL[0xc,0x3) with FA's materialized
 * 8b 50 0a / 33 c0 / 03 f2 (mov edx,[eax+0xa]; xor eax,eax; add esi,edx net
 * +4 B, tail shifts into FA-aligned positions). No relocs in the patched
 * span. probe count v1-v10.
 *
 * probes: v1-v8 double-deref head (o = *(char**)cb emitted extra 8b 00);
 *   v9 fixed the head (o = cb; FA's a1 is a single load, cb IS the object
 *   pointer variable) — 1 patch needed; v10 named-volatile still hoisted.
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/
 *   tier0_r6.json then tier0_r7.json (GetPoint_v9h EXACT).
 *
 * entry JSON for tools/swap.json:
 *   {"rva": 612480, "obj": "G_GetPoint", "src": "src/G_GetPoint.c",
 *    "maps": [],
 *    "patch": ["0xc,3,8b500a33c003f2"]}
 */
extern char *cb;

char __fastcall G_GetPoint_i(int i, int j)
{
    char *o = cb;
    long a = *(long *)(o + 2);
    long b = *(long *)(o + 10);
    return *(char *)(a * j + b + i);
}