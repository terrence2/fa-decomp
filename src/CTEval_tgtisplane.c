// _CTEval_tgtisplane @ rva 0x64190 — tgtisfighter with flag 0xc000.
extern char serviceTicks[];
extern int CTEval_tgtclass(void);

int CTEval_tgtisplane_q(void)
{
    long t = *(long *)((char *)serviceTicks + 0xf4);
    if (*(long *)((char *)t + 0x34) < 0xa00)
        return 0;
    return CTEval_tgtclass() & 0xc000;
}
