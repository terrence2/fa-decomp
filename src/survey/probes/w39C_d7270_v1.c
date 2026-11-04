/* w39C v1: FA 0xd7270 __unlock_file (twin of 0xd7200 __lock_file)
 * if pf in [__stdbuf+0x18, __stdbuf+0x278] -> _unlock(0x1c + (pf - (__stdbuf+0x18)) >> 5)
 * else LeaveCriticalSection(pf + 0x20)
 */
extern char stdbufX[];      /* map _stdbufX=__stdbuf */
extern void unlockX(int);   /* map _unlockX=__unlock */
__declspec(dllimport) void __stdcall LeaveCriticalSectionX(void *);  /* map __imp__LeaveCriticalSectionX@4=__imp__LeaveCriticalSection */

void __cdecl unlock_file(void *pf)
{
    if ((char *)pf >= (char *)stdbufX + 0x18 &&
        (char *)pf <= (char *)stdbufX + 0x278)
        unlockX(0x1c + (((char *)pf - ((char *)stdbufX + 0x18)) >> 5));
    else
        LeaveCriticalSectionX((char *)pf + 0x20);
}