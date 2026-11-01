// _CTEval_wm_hspacing_is @ rva 0x64bb0 (16 B) — movsx eax,word [+0xfd]
extern unsigned char curThing[];

long __cdecl CTEval_wm_hspacing_is(void)
{
    return *(short *)(curThing + 0xfd);
}
