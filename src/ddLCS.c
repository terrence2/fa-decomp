// ?ddLCS@CDirDraw@@SAXXZ @ rva 0x1dfd0 (32 B) — same a0/test/je guard shape as
//   ddECS with the LeaveCriticalSection IAT thunk. Plain C (KEYECS recipe).
extern char ddCsAliveArr[];   // ?criticalSectionAlive@@3DA
extern char ddCsArr[];        // ?m_criticalSection@@3U_RTL_CRITICAL_SECTION@@A
__declspec(dllimport) void __stdcall LeaveCriticalSectionX(void *a);

void ddLCS_q(void)
{
    if (*ddCsAliveArr)
        LeaveCriticalSectionX(ddCsArr);
}