// _CTEval_tgt @ rva 409808 (0x640d0, 64 B) — plain C.  Decisive lever: a
//   TWO-LABEL goto structure that defeats CL's identical-tail merge.  FA
//   has a mid inline ret-0 block (33 c0 c3, target of the 4th gate's ==0
//   fallthrough) BEFORE the ret-1 block (b8 01 00 00 00 c3), plus a SEPARATE
//   end ret-0 block the two EARLY gates jump FORWARD to (74 2e / 74 21);
//   v1-v3 (single ret-0 / return-0 forms) made CL merge the early rets
//   inline and invert the polarity to jne +3.  With inl0/endfail split,
//   CL keeps FA's block order and all four gate opcodes/polarities byte-
//   identical: cmp word [serviceTicks+0x20],0 / je; q=[+0xf4] & 1 / je;
//   byte [+0xe8] / je ret-1; byte [q+0xe3] / jne ret-1 with inline ret-0;
//   and the same trailer pad census as FA.
//   Probe build/survey/probes/p_w23_CTEval_tgt_v4.obj EXACT (w23_r7.json;
//   ladder w23_CTEval_tgt_v1..v3).  Sibling _CTEval_tgtattackinganyone was
//   built out-of-band but its chunk belongs to the w19 wave (src untouched).
//   Maps (swap.json verbatim): [].
extern char serviceTicks[];

long CTEval_tgt_q(void)
{
    if (*(unsigned short *)(serviceTicks + 0x20) == 0)
        goto endfail;
    if ((*(unsigned long *)(*(unsigned long *)(serviceTicks + 0xf4) + 1) & 1) == 0)
        goto endfail;
    if (*(char *)(serviceTicks + 0xe8) == 0)
        goto retone;
    if (*(unsigned char *)(*(unsigned long *)(serviceTicks + 0xf4) + 0xe3) != 0)
        goto retone;
inl0:
    return 0;
retone:
    return 1;
endfail:
    return 0;
}