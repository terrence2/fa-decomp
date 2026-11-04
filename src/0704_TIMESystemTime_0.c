/* w40D_84af0 v2: dllimport GetLocalTime (CL then emits ff 15 IAT call);
 * FA reads wHour/wMinute/wSecond/wMilliseconds (st at [esp] pre-call).
 */
typedef struct {
    unsigned short wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute,
                   wSecond, wMilliseconds;
} SYST;

__declspec(dllimport) void __stdcall GetLocalTime(SYST *);
extern double dTick4;    /* _timerTicks+0x4 (double) */

long __stdcall TIMESystemTime(void)
{
    SYST st;
    long t;
    GetLocalTime(&st);
    t = ((st.wHour * 60 + st.wMinute) * 60 + st.wSecond) * 1000
        + st.wMilliseconds;
    return (long)((double)t / dTick4);
}