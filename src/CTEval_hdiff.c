// _CTEval_hdiff @ rva 0x64910 (28 B) — movsx word reads of _curThing+0x1d and
//   the target thing's +0x1d (which CL sets up first), / 0xb6 via cdq/idiv
//   (probe d135_hd1).
extern char curThing[];
extern char serviceTicks[];
int CTEval_hdiff_q(void)
{
    return (*(short *)(curThing + 0x1d) - *(short *)(*(long *)(serviceTicks + 0xf4) + 0x1d)) / 0xb6;
}
