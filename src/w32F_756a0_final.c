extern int g_dfull;

__declspec(dllimport) void __stdcall SystemParametersInfoA(unsigned long,
    unsigned long, void *, unsigned long);

void __cdecl w32f_spirestore(void)
{
    if (g_dfull)
        SystemParametersInfoA(0x11, 1, 0, 2);
}