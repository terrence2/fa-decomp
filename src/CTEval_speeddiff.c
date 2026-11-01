// _CTEval_speeddiff @ rva 0x64570 (18 B) — direct field read of
//   _curThing+0x34 (a1 moffs) minus the same offset through the target thing
//   pointer, sar eax,8 (probe d131; CTEval_speed reads the same field).
extern char curThing[];
extern char serviceTicks[];
int CTEval_speeddiff_q(void)
{
    return ((*(long *)(curThing + 0x34) - *(long *)(*(long *)(serviceTicks + 0xf4) + 0x34)) >> 8);
}
