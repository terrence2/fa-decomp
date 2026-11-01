// _CTEval_minaltdiff @ rva 0x64780 (23 B) — maxaltdiff at _curThingType+0x75
//   (probe d134).
extern char curThingType[];
extern char serviceTicks[];
int CTEval_minaltdiff_q(void)
{
    return ((*(long *)(curThingType + 0x75) - *(long *)(*(long *)(*(long *)(serviceTicks + 0xf4) + 5) + 0x75)) >> 8);
}
