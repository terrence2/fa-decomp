// _AlmostHome@0 @ rva 0x800a0 (74 B code + pad) — h=APHomeAirport();
// nonzero -> d=Dist(_thing11, objPtrs[uword][_curThing+0xe6]+0x11);
// zero -> d=0x7fffffff (b8 imm32, jmp'd over); return d<0xa50000 &&
// thing15<0x4e2000 as an AL result (b0 01 / 32 c0 — char return type).
// xor ecx,ecx + 66 8b 88 word load into cx + sib-85 8b 04 8d objPtrs
// index, 3d/7d A-forms, a1 thing15 moffs, push imm32 0x508749 (HIGHLOW
// on _thing11). All elided by dis.py; reproduced in plain C with the
// ushort-typed w local and a __stdcall unsigned char return.
extern long objPtrs[];
extern char thing11[];
extern long thing15;
extern long __stdcall APHomeAirport(void);
extern long __stdcall Dist(char *a, char *b);

unsigned char __stdcall AlmostHome(void)
{
    long h;
    unsigned short w;
    long d;

    h = APHomeAirport();
    if (h != 0) {
        w = *(unsigned short *)((char *)h + 0xe6);
        d = Dist(thing11, (char *)objPtrs[w] + 0x11);
    } else {
        d = 0x7fffffff;
    }
    return d < 0xa50000 && thing15 < 0x4e2000;
}