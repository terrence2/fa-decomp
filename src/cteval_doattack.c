// _CTEval_do_attack @ rva 0x64010 (16 B) — tick == 2
extern unsigned short serviceTicks[];

long __cdecl CTEval_do_attack(void)
{
    return *(unsigned short *)(serviceTicks + 0x28) == 2;
}
