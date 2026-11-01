// _CTEval_corner @ rva 0x645c0 (16 B) — jmp _COCornerSpeed@0 (same target!)
extern long __stdcall COCornerSpeed(void);

long __cdecl CTEval_corner(void)
{
    return COCornerSpeed();
}
