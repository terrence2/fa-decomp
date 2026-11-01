// _CTEval_twrdiff @ rva 0x64650 (16 B) — push &COTwr / call
extern long __cdecl CTVarDiff(long (__stdcall *)(void));
extern long __stdcall COTwr(void);

long __cdecl CTEval_twrdiff(void)
{
    return CTVarDiff(COTwr);
}
