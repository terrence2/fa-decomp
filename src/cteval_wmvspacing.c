// _CTEval_wm_vspacing_is @ rva 0x64bc0 (16 B) — movsx eax,word [+0xff]
extern unsigned char curThing[];

long __cdecl CTEval_wm_vspacing_is(void)
{
    return *(short *)(curThing + 0xff);
}
