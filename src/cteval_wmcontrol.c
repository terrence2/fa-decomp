// _CTEval_wm_control_is @ rva 0x64be0 (16 B) — xor eax,eax / mov al,[+0xfb]
extern unsigned char curThing[];

long __cdecl CTEval_wm_control_is(void)
{
    return *(unsigned char *)(curThing + 0xfb);
}
