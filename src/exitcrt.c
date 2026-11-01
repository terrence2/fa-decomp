// __exit (= CRT public _exit) @ rva 0xd3870 (18 B) — mov eax,[esp+4] /
//   push 0 / push 1 / push eax / call $FA$t_4d38b0 (_doexit(code, quick=1,
//   retcode=0)) / add esp,0xc / ret. C ident _exit compiles to symbol
//   __exit — identity with the chunk name.
extern void exitHelper(int code, int quick, int retcode);

void __cdecl _exit(int c)
{
    exitHelper(c, 1, 0);
}