// _CTEval_p @ rva 0x648d0 — 16-bit divide of *(short*)(curThing+0x1f) by 0xb6
//   (cwd/idiv cx via a short divisor variable, movsx widen — probe d53 exact).
extern char curThing[];

int CTEval_p_q(void)
{
    short v = *(short *)((char *)curThing + 0x1f);
    short q = 0xb6;
    return (int)(v / q);
}
