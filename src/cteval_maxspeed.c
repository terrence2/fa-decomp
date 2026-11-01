// _CTEval_maxspeed @ rva 0x64600 (16 B) — jmp _COMaxSpeed@0
extern long __stdcall COMaxSpeed(void);

long __cdecl CTEval_maxspeed(void)
{
    return COMaxSpeed();
}
