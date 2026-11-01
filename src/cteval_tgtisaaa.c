// _CTEval_tgtisaaa @ rva 0x641d0 (16 B) — and eax,0x800
extern long __cdecl CTEval_tgtclass(void);

long __cdecl CTEval_tgtisaaa(void)
{
    return CTEval_tgtclass() & 0x800;
}
