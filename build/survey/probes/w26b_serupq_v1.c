// ?SER_UpdateRemoteQueueStatus@@YAXJ@Z @ rva 0x90460 — C v1
extern long serQtailGX;         /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x1a4 */

void __cdecl SER_UpdateRemoteQueueStatusq(long target)
{
    for (;;)
    {
        if ((*(unsigned long *)serQtailGX & 0xff) == (unsigned long)target)
            return;
        *(unsigned long *)serQtailGX = *(unsigned long *)serQtailGX + 1;
    }
}
