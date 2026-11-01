// _CTEval_minspeed @ rva 0x64590 (16 B) — jmp _COMinSpeed@0
extern long __stdcall COMinSpeed(void);

long __cdecl CTEval_minspeed(void)
{
    return COMinSpeed();
}
