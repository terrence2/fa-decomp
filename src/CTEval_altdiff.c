// _CTEval_altdiff @ rva 0x64700 (18 B) — speeddiff shape at field offset
//   0x15 (probe d132).
extern char curThing[];
extern char serviceTicks[];
int CTEval_altdiff_q(void)
{
    return ((*(long *)(curThing + 0x15) - *(long *)(*(long *)(serviceTicks + 0xf4) + 0x15)) >> 8);
}
