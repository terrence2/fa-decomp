// ?SER_UpdateRemoteQueueStatus@@YAXJ@Z @ rva 0x90460 — C v3 (FA body is
// a1/40/a3 with the bottom test on the leftover eax — that is the shape of
// `status = ++t;` where the increment's result feeds a local: load, inc,
// store, then status lives in the same reg)
extern unsigned long serQtailG;   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x1a4 */

void __cdecl SER_UpdateRemoteQueueStatusq(long target)
{
    unsigned long status;

    status = serQtailG;
    while ((status & 0xff) != (unsigned long)target)
        status = ++serQtailG;
}