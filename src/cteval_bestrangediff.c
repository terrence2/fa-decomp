// _CTEval_bestrangediff @ rva 0x64250 (16 B) — push &CTEval_bestrange /
//   call CTVarDiff / add esp,4 / ret
extern long __cdecl CTVarDiff(long (__cdecl *)(void));
extern long __cdecl CTEval_bestrange(void);

long __cdecl CTEval_bestrangediff(void)
{
    return CTVarDiff(CTEval_bestrange);
}
