// _CTEval_do_radar_launch @ rva 0x64020 (16 B) — tick == 3
extern unsigned short serviceTicks[];

long __cdecl CTEval_do_radar_launch(void)
{
    return *(unsigned short *)(serviceTicks + 0x28) == 3;
}
