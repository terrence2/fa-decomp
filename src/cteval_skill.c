// _CTEval_skill @ rva 0x64880 (16 B) — xor eax,eax / mov al,[+0xe2] / ret
extern unsigned char curThing[];

long __cdecl CTEval_skill(void)
{
    return *(unsigned char *)(curThing + 0xe2);
}
