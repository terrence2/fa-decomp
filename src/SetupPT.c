// _SetupPT @ rva 0xa40c0 (16 B) — mov eax,[esp+4] / push eax / call _SetupNT /
//   add esp,4 / ret — cdecl forwarder.
extern void __cdecl SetupNT(int a);

void __cdecl SetupPT(int a)
{
    SetupNT(a);
}