/* w42C cand3: _TIMEGetMillis @0x84dd0 (112 B) — cdecl 0 params, long return. */
__declspec(dllimport) void __stdcall QueryPerformanceCounter(void *out);
extern char w42c_sleep[];              /* ?noTimerSleep@@3JA */
extern char w42c_curT[];               /* _currentT */

long __cdecl TIMEGetMillis(void)
{
    __int64 now, m;

    if (*(long *)&w42c_sleep[0xc] == 0 && *(long *)&w42c_sleep[8] == 0)
        return 0;
    QueryPerformanceCounter(&now);
    m = now - *(__int64 *)&w42c_curT[8];
    m = m * 1000;
    return (long)(m / *(__int64 *)&w42c_sleep[8]);
}
