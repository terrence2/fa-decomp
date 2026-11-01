// _CTEval_turnratediff @ rva 0x64690 — CTVarDiff((int)COTurnRate) / 0xb6
//   (mov ecx,0xb6 / cdq / idiv ecx — probe d52 exact).
extern int CTVarDiff(int v);
extern int COTurnRate(void);

int CTEval_turnratediff_q(void)
{
    int r = CTVarDiff((int)COTurnRate);
    return r / 0xb6;
}
