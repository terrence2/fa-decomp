// _CTEval_cornerspeed @ rva 0x645b0 (16 B) — jmp _COCornerSpeed@0
extern long __stdcall COCornerSpeed(void);

long __cdecl CTEval_cornerspeed(void)
{
    return COCornerSpeed();
}
