// ?ddECS@CDirDraw@@SAXXZ @ rva 0x1dfb0 (32 B) — FA asm: a0 [criticalSectionAlive]
//   / test al,al / je L / push offset m_criticalSection / call [__imp__EnterCriticalSection]
//   / L: ret. Critical-section Enter guard. Plain C: a0 byte read + push offset
//   reproduced via KEYECS recipe (extern char[] + *arr deref, dllimport stdcall
//   extern gives the ff 15 IAT call). Maps: two C++-decorated CDirDraw globals.
extern char ddCsAliveArr[];   // ?criticalSectionAlive@@3DA
extern char ddCsArr[];        // ?m_criticalSection@@3U_RTL_CRITICAL_SECTION@@A
__declspec(dllimport) void __stdcall EnterCriticalSectionX(void *a);

void ddECS_q(void)
{
    if (*ddCsAliveArr)
        EnterCriticalSectionX(ddCsArr);
}