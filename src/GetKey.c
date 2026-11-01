// _GetKey @ rva 0x126f0 (64 B) — FA asm: call _GetKey2 / cmp eax,0x2f07 /
//   jne ret / cmp word <_curScreen>,0x10 / jne dump / mov cl,<menuSel+4> /
//   test cl,cl / jne dump / mov cl,<dialogOn> / test cl,cl / je ret / dump:
//   call _ScreenDump@0 / xor eax,eax / ret.  Three redraw-guards; curScreen
//   and menuSelecting short-circuit straight into the shared dump block,
//   dialogOn is the inverted if(!dialogOn) return-k guard.  Plain C with one
//   dump label reached by two gotos: the ||-merge form made CL duplicate the
//   dump block (identical tails not merged) and the pure-|| form flipped the
//   dialogOn jne/je — the goto layout gives FA's 75/75/74 jumper set with a
//   single c3.  Sibling GetKeySlow (wave 17) tail-jmps here.
//   Probe b18_GetKey_v3.obj — exact modulo fixup dwords.
extern int __cdecl GetKey2(void);
extern void __stdcall ScreenDump(void);
extern unsigned short curScreen;
extern char menuSelecting[];
extern char dialogOn;

int GetKey(void)
{
    int k;
    k = GetKey2();
    if (k != 0x2f07) return k;
    if ((unsigned short)curScreen != 0x10) goto dump;
    if (menuSelecting[4]) goto dump;
    if (!dialogOn) return k;
dump:
    ScreenDump();
    return 0;
}