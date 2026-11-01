// _exit (= public exit) @ rva 0xd3850 (18 B) — mov eax,[esp+4] / push 0 /
//   push 0 / push eax / call $FA$t_4d38b0 (_doexit(code, quick=0, retcode
//   =0)) / add esp,0xc / ret. (The chunk is named _exit because the C ident
//   `exit` compiles to symbol _exit.)
extern void exitHelper(int code, int quick, int retcode);

void __cdecl exit_(int c)
{
    exitHelper(c, 0, 0);
}