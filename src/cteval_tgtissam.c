// _CTEval_tgtissam @ rva 0x641c0 (16 B) — and eax,0x1000
extern long __cdecl CTEval_tgtclass(void);

long __cdecl CTEval_tgtissam(void)
{
    return CTEval_tgtclass() & 0x1000;
}
