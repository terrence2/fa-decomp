// _CTEval_tgtisship @ rva 0x641b0 (16 B)
// FA: call _CTEval_tgtclass / and eax,0x2000 / ret
extern long __cdecl CTEval_tgtclass(void);

long __cdecl CTEval_tgtisship(void)
{
    return CTEval_tgtclass() & 0x2000;
}
