// _CTEval_radar @ rva 0x64260 (16 B) — a1 moffs deref + and 0x800
extern unsigned char curThing[];

long __cdecl CTEval_radar(void)
{
    return *(unsigned *)(curThing + 0xde) & 0x800;
}
