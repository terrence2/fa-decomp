// ?SER_Resume@@YAXXZ @ rva 0x4b820 (32 B) — FA asm: e8
//   ?SER_EnterCriticalCodeForeground@@YAXXZ (call)/c7 05 <Ctrl+0x1e4>,0
//   (dword zero-store serSuspBase)/a0 <Ctrl+0x33d>/a2 <Ctrl+0x33c> (byte
//   copy serAltLock -> serSuspLock, acc moffs forms)/e9 jmp-tail
//   ?SER_LeaveCriticalCodeForeground@@YAXXZ.  Twin of src/SER_Suspend.c
//   (wave-19 SER_Suspend anchor band).  Plain C reached everything except
//   the byte copy: CL 4.2 streams scalar-to-scalar byte globals as 8a 0d/
//   88 0d (cl forms — v1/v2 probes, incl. the array-[0] spelling), its a0/
//   a2 acc-moffs forms firing only when BOTH operands carry interior disp
//   (CPToggleHistory/w6_t7 precedent), so the copy goes through ONE
//   ?Ctrl@@...-anchored byte array with +0x33c/+0x33d element offsets.
//   Probe build/w4probe/b20f_SER_Resume.obj — exact modulo fixup dwords.
extern unsigned char serCtl[];   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */

extern void serEnterC(void);        /* ?SER_EnterCriticalCodeForeground@@YAXXZ */
extern void serLeaveC(void);        /* ?SER_LeaveCriticalCodeForeground@@YAXXZ */

void SER_Resume_q(void)
{
    serEnterC();
    *(long *)&serCtl[0x1e4] = 0;
    serCtl[0x33c] = serCtl[0x33d];
    serLeaveC();
}