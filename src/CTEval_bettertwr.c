// _CTEval_bettertwr @ rva 0x64660 — betterspeed with COTwr and threshold 0x0a.
extern int CTVarDiff(int v);
extern int COTwr(void);

int CTEval_bettertwr_q(void)
{
    int b = 0;
    int r = CTVarDiff((int)COTwr);
    b = r >= 0x0a;
    return b;
}
