// _SetupJT @ rva 0xa40d0 (16 B) — mov eax,[esp+4] / push eax / call _SetupOT /
//   add esp,4 / ret — cdecl forwarder.
extern void __cdecl SetupOT(int a);

void __cdecl SetupJT(int a)
{
    SetupOT(a);
}