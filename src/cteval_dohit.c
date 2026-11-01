// _CTEval_do_hit @ rva 0x64040 (16 B) — tick == 5
extern unsigned short serviceTicks[];

long __cdecl CTEval_do_hit(void)
{
    return *(unsigned short *)(serviceTicks + 0x28) == 5;
}
