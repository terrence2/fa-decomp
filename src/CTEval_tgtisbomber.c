// _CTEval_tgtisbomber @ rva 0x64170 — tgtisfighter with flag 0x4000.
extern char serviceTicks[];
extern int CTEval_tgtclass(void);

int CTEval_tgtisbomber_q(void)
{
    long t = *(long *)((char *)serviceTicks + 0xf4);
    if (*(long *)((char *)t + 0x34) < 0xa00)
        return 0;
    return CTEval_tgtclass() & 0x4000;
}
