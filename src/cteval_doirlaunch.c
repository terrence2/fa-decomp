// _CTEval_do_ir_launch @ rva 0x64030 (16 B) — tick == 4
extern unsigned short serviceTicks[];

long __cdecl CTEval_do_ir_launch(void)
{
    return *(unsigned short *)(serviceTicks + 0x28) == 4;
}
