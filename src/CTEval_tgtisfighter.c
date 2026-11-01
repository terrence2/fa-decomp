// _CTEval_tgtisfighter @ rva 0x64150 — serviceTicks+0xf4 struct pointer,
//   class field +0x34 below the 0xa00 ceiling, then the class-bit test
//   (probe d47 exact; bomber = 0x4000, plane = 0xc000 copies).
extern char serviceTicks[];
extern int CTEval_tgtclass(void);

int CTEval_tgtisfighter_q(void)
{
    long t = *(long *)((char *)serviceTicks + 0xf4);
    if (*(long *)((char *)t + 0x34) < 0xa00)
        return 0;
    return CTEval_tgtclass() & 0x8000;
}
