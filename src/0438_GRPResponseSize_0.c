// @GRPResponseSize@0 @ rva 389712 (0x5f250, 48 B) — plain C.  Decisive
//   levers: FA re-reads the global for the byte (a1 reload — global not
//   cached in a local), flag byte kept in AL across both masks, and the tail
//   `b & 0x10 ? 2 : 100` spelled as the BriefMap wave-19 sbb recipe
//   ((b & 0x10) >= 1 ? 2 : 100 → cmp al,1 / sbb eax,eax / and 0x62 / add 2).
//   Probe build/survey/probes/p_w23_GRPResponseSize_v2.obj EXACT
//   (w23_r2.json).  Maps (swap.json verbatim): _grpPtr=_curThing+0xe8.
extern long grpPtr;

long GRPResponseSize_q(void)
{
    unsigned char b;
    if (grpPtr == 0)
        return 100;
    b = *(unsigned char *)grpPtr;
    if (b & 8)
        return 1;
    return ((b & 0x10) >= 1) ? 2 : 100;
}