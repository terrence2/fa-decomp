// ?SER_Suspend@@YAXXZ @ rva 0x4b800 (32 B) — FA asm: e8 ?SER_EnterCriticalCodeForeground@@YAXXZ
//   (call)/c6 05 <Ctrl+0x33c>,1/c7 05 <Ctrl+0x1e4>,0/e9 jmp-tail
//   ?SER_LeaveCriticalCodeForeground@@YAXXZ.  Plain C reproduces it exactly:
//   CL 4.2 emits the last void cdecl call as an e9 tail jmp (d63 family),
//   the byte store as c6 05 and the 0 dword store as c7 05.  Probe
//   build/w4probe/w19_sersuspend_v1.obj — exact (v2 fastcall-zero-arg variant
//   assembled the same bytes; v1 kept for the cdecl map spelling).
extern unsigned char serSuspLock;   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x33c */
extern long serSuspBase;            /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x1e4 */

extern void serEnterC(void);        /* ?SER_EnterCriticalCodeForeground@@YAXXZ */
extern void serLeaveC(void);        /* ?SER_LeaveCriticalCodeForeground@@YAXXZ */

void SER_Suspend_q(void)
{
    serEnterC();
    serSuspLock = 1;
    serSuspBase = 0;
    serLeaveC();
}