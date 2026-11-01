// _CTEval_ir @ rva 0x642a0 (16 B) — same field as radar, mask 0x1000
extern unsigned char curThing[];

long __cdecl CTEval_ir(void)
{
    return *(unsigned *)(curThing + 0xde) & 0x1000;
}
