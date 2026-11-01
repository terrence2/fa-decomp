// _CTEval_maxaltdiff @ rva 0x64750 (23 B) — curThingType+0x79 minus a double
//   deref: *(long *)(tgtPtr + 5) then +0x79, sub eax,[edx+0x79] folded, sar
//   eax,8. FA's push ebx/pop ebx (dead save) reproduces naturally in C — the
//   three-reg expression forces CL to spill to ebx too (d133_mad1 == mad2).
extern char curThingType[];
extern char serviceTicks[];
int CTEval_maxaltdiff_q(void)
{
    return ((*(long *)(curThingType + 0x79) - *(long *)(*(long *)(*(long *)(serviceTicks + 0xf4) + 5) + 0x79)) >> 8);
}
