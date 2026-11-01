// _CTEval_turnrate @ rva 0x64680 (16 B)
// FA: call _COTurnRate@0 / cdq / mov ecx,0xb6 / idiv ecx / ret
extern long __stdcall COTurnRate(void);

long __cdecl CTEval_turnrate(void)
{
    return COTurnRate() / 182;
}
