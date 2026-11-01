// _CTEval_maxspeeddiff @ rva 0x64610 (16 B) — push &COMaxSpeed / call
extern long __cdecl CTVarDiff(long (__stdcall *)(void));
extern long __stdcall COMaxSpeed(void);

long __cdecl CTEval_maxspeeddiff(void)
{
    return CTVarDiff(COMaxSpeed);
}
