#pragma optimize("y", off)
__declspec(dllimport) void __stdcall EnterCriticalSection(void *a);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *a);
extern unsigned char Ctrl[];
void __stdcall SER_LeaveCriticalCodeBackground(void)
{
    EnterCriticalSection(Ctrl);
    *(unsigned char *)(Ctrl + 0x1c) = 0;
    LeaveCriticalSection(Ctrl);
}