// __cexit @ rva 0xd3890 (15 B, FPO cbProlog=0)
// FA asm: push 1 / push 0 / push 0 / call 0x4d38b0 / add esp,0xc / ret
//   -> cdecl _doexit(0, 0, 1); the callee chunk is UNNAMED, so fitobj gets
//      a map _doexit=$FA$_t_4d38b0 (addend 0).
extern void __cdecl _doexit(int, int, int);

void __cdecl _cexit(void)
{
    _doexit(0, 0, 1);
}