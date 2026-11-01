// _CTEval_maxrangediff @ rva 0x64220 (28 B) — flag byte at _serviceTicks+0xe8
//   routes to a cdecl function-pointer call into CTVarDiff (non-tail: call,
//   add esp,4, ret) or to a no-arg tail jmp e9 into CTEval_maxrange; the
//   je 74 0e skips the whole call block (probe d129_mrd2; zero-first polarity
//   gives jne + short tail-jmp instead, d129_mrd1).
extern char serviceTicks[];
extern long __cdecl CTVarDiff(long (__stdcall *)(void));
extern long __cdecl CTEval_maxrangeFn(void);
int CTEval_maxrangediff_q(void)
{
    if (serviceTicks[0xe8] != 0)
        return (int)CTVarDiff((long (__stdcall *)(void))CTEval_maxrangeFn);
    return (int)CTEval_maxrangeFn();
}
