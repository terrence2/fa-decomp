// _ClearCachedFilenames @ rva 0xaa240 — push 1 / call _LibraryShutdown /
//   add esp,4 / call _LibraryStartup / jmp _NamesShutdown@0, plus pads.
//   The 0-arg void call tail-jmps (proven pattern); _NamesShutdown@0 needs
//   its own map because the FA symbol carries the stdcall decoration.
extern int __cdecl LibraryShutdown(int f);
extern void __cdecl LibraryStartup(void);
extern void NamesShutdown(void);

void ClearCachedFilenames_q(void)
{
    LibraryShutdown(1);
    LibraryStartup();
    NamesShutdown();
}
