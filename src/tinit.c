// _T_Init@0 @ rva 0xc2110 (16 B) — pure tail jmp (T_Init forwards to
//   its sibling T_Shutdown)
extern void __stdcall T_Shutdown(void);

void __stdcall T_Init(void)
{
    T_Shutdown();
}
