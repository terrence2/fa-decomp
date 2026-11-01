// _CTEval_minspeeddiff @ rva 0x645a0 (16 B) — push &COMinSpeed / call
extern long __cdecl CTVarDiff(long (__stdcall *)(void));
extern long __stdcall COMinSpeed(void);

long __cdecl CTEval_minspeeddiff(void)
{
    return CTVarDiff(COMinSpeed);
}
