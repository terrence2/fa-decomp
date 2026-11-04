/* w42C cand4: _InstallTimerInt @0x84f40 (96 B) — cdecl 0 params. */
__declspec(dllimport) void __stdcall QueryPerformanceFrequency(__int64 *f);
__declspec(dllimport) void __stdcall QueryPerformanceCounter(__int64 *c);
__declspec(dllimport) unsigned long __stdcall CreateThread(
    long a1, long a2, unsigned long (__stdcall *proc)(unsigned long),
    long a4, long a5, long *id);
extern unsigned long __stdcall w42c_StartThread(unsigned long);
extern void __cdecl ErrorExit(char *msg);
extern char w42c_sleep[];              /* ?noTimerSleep@@3JA; freq at +8, err text at +0x20 */
extern char w42c_curT8[];              /* _currentT+8 */
extern long w42c_timerTicks;           /* _timerTicks */
extern long w42c_lastTicks;            /* _lastTicks */
extern long w42c_hTimeThread;          /* _hTimeThread */
extern long w42c_dwTimeThreadID;       /* _dwTimeThreadID */

void __cdecl w42c_InstallTimerInt(void)
{
    QueryPerformanceFrequency((__int64 *)&w42c_sleep[8]);
    if (*(long *)&w42c_sleep[0xc] == 0 && *(long *)&w42c_sleep[8] == 0)
        ErrorExit(&w42c_sleep[0x20]);
    QueryPerformanceCounter((__int64 *)w42c_curT8);
    w42c_timerTicks = 0;
    w42c_lastTicks = 0;
    w42c_hTimeThread = CreateThread(0, 0, w42c_StartThread, 0, 0,
                                    &w42c_dwTimeThreadID);
}
