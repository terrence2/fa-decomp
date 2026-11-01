// __lockexit @ rva 0xd3970 (11 B, FPO cbProlog=0)
// FA asm: push 0xd / call __lock / add esp,4 / ret
//   -> cdecl call, exit-lock #13, no tail-jmp possible (caller cleans).
extern void __cdecl _lock(int);

void __cdecl _lockexit(void)
{
    _lock(13);
}