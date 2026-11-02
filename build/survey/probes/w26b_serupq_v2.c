// ?SER_UpdateRemoteQueueStatus@@YAXJ@Z @ rva 0x90460 — C v2 (volatile global RMW)
extern volatile unsigned long serQtailG;  /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x1a4 */

void __cdecl SER_UpdateRemoteQueueStatusq(long target)
{
    while ((serQtailG & 0xff) != (unsigned long)target)
        serQtailG++;
}
