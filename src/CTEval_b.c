// _CTEval_b @ rva 0x648f0 — CTEval_p at curThing+0x21.
extern char curThing[];

int CTEval_b_q(void)
{
    short v = *(short *)((char *)curThing + 0x21);
    short q = 0xb6;
    return (int)(v / q);
}
