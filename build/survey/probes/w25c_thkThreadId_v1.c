// 0xd9270 = 890736, unnamed gap, 6 B — IAT pass-through thunk:
// ff 25 3ca55800  jmp [__imp__GetCurrentThreadId]  (no rel32 refs anywhere)
__declspec(dllimport) unsigned long __stdcall CurrentThreadIdApi(void);
/* map __imp__CurrentThreadIdApi@0=__imp__GetCurrentThreadId */

unsigned long __stdcall w25c_thkGetCurThreadId(void)
{
    return CurrentThreadIdApi();
}