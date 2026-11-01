// _CTEval_wm_formation_is @ rva 0x64bd0 (16 B) — xor eax,eax / mov al/[+0xfc]
extern unsigned char curThing[];

long __cdecl CTEval_wm_formation_is(void)
{
    return *(unsigned char *)(curThing + 0xfc);
}
