/* ?SER_EnterCriticalCodeBackground@@YAXXZ (rva 0x980d0, 96 B): serial
 * server background wait. Enter the critical section on ?Ctrl, then -
 * while the busy flag byte at ?Ctrl+0x1c is still set - leave, sleep,
 * re-enter, retest. When the wait is done, raise the flag byte itself
 * (c6 05 [Ctrl+0x1c],1) and leave once more. Both wait-exit paths merge
 * at the flag store (jmp +0x6 over the exit arm's duplicated
 * LeaveCriticalSection IAT load - scheduler dead-code duplication kept by
 * the transplant). All 5 Ctrl pushes, 3 flag loads and the flag store are
 * DIR32 sites; the 4 IAT loads are identity __imp__ sites; FA calls the
 * three kernel32 entries through register moves (ff d7 / ff d5 / ff d6).
 */
extern void *__imp__EnterCriticalSection;
extern void *__imp__Sleep;
extern void *__imp__LeaveCriticalSection;

void __cdecl w44e_EnterCriticalCodeBackground(void)
{
    ((void (__cdecl *)(void *)) __imp__LeaveCriticalSection)(0);
    ((void (__cdecl *)(unsigned long)) __imp__Sleep)(0);
    ((void (__cdecl *)(void *)) __imp__EnterCriticalSection)(0);
    ((void (__cdecl *)(void *)) __imp__LeaveCriticalSection)(0);
}