// _CTEval_bestrange @ rva 0x64240 (16 B) — call _CTEval_maxrange / sar eax,1
extern long __cdecl CTEval_maxrange(void);

long __cdecl CTEval_bestrange(void)
{
    return CTEval_maxrange() >> 1;
}
