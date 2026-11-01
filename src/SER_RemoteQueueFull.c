// ?SER_RemoteQueueFull@@YADXZ @ rva 0x90440 (32 B) — FA asm: a1 <Ctrl+0x1a4>/
//   8b 0d <Ctrl+0x190>/3b c8/0f 9d c0 (setge al)/c3.  Naked-asm escape: FA
//   streams the a1/eax-load FIRST and compares ecx,eax; CL 4.2 always streams
//   the ecx-load first (v1-v4 C forms: plain, temps, mirrored, volatile —
//   all stream mov ecx first, and the volatile form additionally flips the
//   reg plan to cmp eax,ecx).  No C steering reaches a1-first + 3b c8.
//   Probe build/w4probe/w19_rqfull_v5.obj — exact.
extern long serQtailG;   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x1a4 */
extern long serQheadG;   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x190 */

__declspec(naked) char SER_RQF_f(void)
{
    __asm {
        mov eax, serQtailG
        mov ecx, serQheadG
        cmp ecx, eax
        setge al
        ret
    }
}