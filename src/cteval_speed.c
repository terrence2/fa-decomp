// _CTEval_speed @ rva 0x64560 (16 B) — sar eax,8 on a signed field
extern unsigned char curThing[];

long __cdecl CTEval_speed(void)
{
    return *(long *)(curThing + 0x34) >> 8;
}
