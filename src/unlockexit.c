// __unlockexit @ rva 0xd3980 (11 B, FPO cbProlog=0)
// FA asm: push 0xd / call __unlock / add esp,4 / ret
extern void __cdecl _unlock(int);

void __cdecl _unlockexit(void)
{
    _unlock(13);
}