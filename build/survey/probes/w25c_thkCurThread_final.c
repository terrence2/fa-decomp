// 0xd9280 = 890752, unnamed gap, 6 B — IAT pass-through thunk:
// ff 25 48a55800  jmp [__imp__GetCurrentThread]
__declspec(dllimport) void * __stdcall CurrentThreadApi(void);
/* map __imp__CurrentThreadApi@0=__imp__GetCurrentThread */

void * __stdcall w25c_thkGetCurThread(void)
{
    return CurrentThreadApi();
}