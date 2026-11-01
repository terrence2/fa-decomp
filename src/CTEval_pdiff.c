// _CTEval_pdiff @ rva 0x64930 (28 B) — hdiff at +0x1f (probe d136).
extern char curThing[];
extern char serviceTicks[];
int CTEval_pdiff_q(void)
{
    return (*(short *)(curThing + 0x1f) - *(short *)(*(long *)(serviceTicks + 0xf4) + 0x1f)) / 0xb6;
}
