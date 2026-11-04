// _CTEval_turnradiusdiff @ rva 0x646c0 (16 B) — push &COTurnRadius / call
extern long __cdecl CTVarDiff(long (__stdcall *)(void));
extern long __stdcall COTurnRadius(void);

long __cdecl CTEval_turnradiusdiff(void)
{
    return CTVarDiff(COTurnRadius);
}
