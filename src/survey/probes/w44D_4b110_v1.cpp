/*
 * w44D_4b110_v1.cpp — ?SER_EnterCriticalCodeForeground@@YAXXZ @ 0x44b110
 * (96 B, frame: 4 saved regs)
 * EnterCriticalSection(&Ctrl); if (Ctrl[0x1c]) do { Leave; Sleep(0);
 * Enter; } while (Ctrl[0x1c]); Ctrl[0x1c] = 1; LeaveCriticalSection(&Ctrl);
 * FA reg-caches __imp__ thunks (edi=Enter, esi=Sleep, ebp=Leave) and
 * zeroes Sleep's arg into ebx.
 */
extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);
__declspec(dllimport) void __stdcall Sleep(unsigned long ms);
}

extern "C" unsigned char Ctrl[];

void SER_EnterCriticalCodeForeground(void)
{
    EnterCriticalSection(&Ctrl);
    if (Ctrl[0x1c]) {
        do {
            LeaveCriticalSection(&Ctrl);
            Sleep(0);
            EnterCriticalSection(&Ctrl);
        } while (Ctrl[0x1c]);
    }
    Ctrl[0x1c] = 1;
    LeaveCriticalSection(&Ctrl);
}