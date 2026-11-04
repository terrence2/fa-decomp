/* w39C v1: FA 0xd7200 __lock_file (twin: 0xd7270 __unlock_file)
 * if pf in [__stdbuf+0x18, __stdbuf+0x278] -> _lock(0x1c + (pf - (__stdbuf+0x18)) >> 5)
 * else EnterCriticalSection(pf + 0x20);  FA frame: push ebp/mov ebp,esp, cdecl (plain ret)
 */
extern char stdbufX[];      /* map _stdbufX=__stdbuf */
extern void lockX(int);     /* map _lockX=__lock */
__declspec(dllimport) void __stdcall EnterCriticalSectionX(void *);  /* map __imp__EnterCriticalSectionX@4=__imp__EnterCriticalSection */

void __cdecl lock_file(void *pf)
{
    if ((char *)pf >= (char *)stdbufX + 0x18 &&
        (char *)pf <= (char *)stdbufX + 0x278)
        lockX(0x1c + (((char *)pf - ((char *)stdbufX + 0x18)) >> 5));
    else
        EnterCriticalSectionX((char *)pf + 0x20);
}