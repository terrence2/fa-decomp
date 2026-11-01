// _ErrorExitNoMem@0 @ rva 0x49a40 (16 B) — push &noMemString / call
//   ErrorExit (cdecl, 1 arg) / add esp,4 / ret
extern void __cdecl ErrorExit(const char *msg);
extern char noMemString[];

void __stdcall ErrorExitNoMem(void)
{
    ErrorExit(noMemString);
}
