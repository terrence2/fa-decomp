// _CTEval_tgthumancontrol @ rva 0x641e0 (27 B) — word==0 gate then byte load
//   through the target-thing pointer at _serviceTicks+0xf4; CL keeps the
//   byte load unwidened (8a 40 10) before and eax,0x80 (probe d128).
extern char serviceTicks[];
int CTEval_tgthumancontrol_q(void)
{
    if (*(short *)(serviceTicks + 0x20) == 0)
        return 0;
    return *(char *)(*(long *)(serviceTicks + 0xf4) + 0x10) & 0x80;
}
