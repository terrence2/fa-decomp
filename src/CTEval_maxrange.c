// _CTEval_maxrange @ rva 0x64200 — v &= 0x800 then "if (v) return 10" and a
//   cmp/sbb/add tail on the SAME masked value (needs unsigned long; probes
//   d48/d64: signed long re-tests give f6-c4 and setge/inc forms instead).
extern char curThing[];

int CTEval_maxrange_q(void)
{
    unsigned long v = *(unsigned long *)((char *)curThing + 0xde);
    v &= 0x800;
    if (v)
        return 10;
    return v >= 1 ? 2 : 1;
}
