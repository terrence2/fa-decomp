// _CTEval_minalt @ rva 0x64770 (16 B) — sar eax,8 on curThingType+0x75
extern unsigned char curThingType[];

long __cdecl CTEval_minalt(void)
{
    return *(long *)(curThingType + 0x75) >> 8;
}
