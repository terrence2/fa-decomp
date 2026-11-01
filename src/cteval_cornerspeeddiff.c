// _CTEval_cornerspeeddiff @ rva 0x645d0 (16 B) — push &COCornerSpeed / call
extern long __cdecl CTVarDiff(long (__stdcall *)(void));
extern long __stdcall COCornerSpeed(void);

long __cdecl CTEval_cornerspeeddiff(void)
{
    return CTVarDiff(COCornerSpeed);
}
