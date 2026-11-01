// _LibraryShutdown @ rva 0x117c0 (16 B) — mov eax,[esp+4] / push eax /
//   call _LibShutDown / add esp,4 / ret — cdecl 1-arg forwarder.
extern void __cdecl LibShutDown(int a);

void __cdecl LibraryShutdown(int a)
{
    LibShutDown(a);
}