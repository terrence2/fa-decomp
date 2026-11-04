/* __lock_fhandle @ 0xd7? rva 0xdeda0 (911520) — FPO/esp, params=1, no locals.
   FA bytes:
     mov eax,[esp+4] / push ebx / push esi / mov ecx,eax / push edi
     and ecx,-25 / sar ecx,3 / and eax,0x1f / shl eax,2
     lea edi,[ecx+__crtheap+0x4] / lea esi,[eax+eax*8]
     mov ebx,[edi] / add ebx,esi
     if ([ebx+8]==0) { __lock(0x11); if ([ebx+8]==0) {
         InitializeCriticalSection(ebx+0xc); ++[ebx+8]; } __unlock(0x11); }
     eax = [edi]+esi+0xc; EnterCriticalSection(eax)
   grp[0] is read twice -> volatile forces the eax reload at the end. */
extern void __cdecl w29c_lockX(int n);        /* __lock */
extern void __cdecl w29c_unlockX(int n);      /* __unlock */
extern void (__stdcall *w29c_icsP)(void *a);  /* _w29c_icsP -> __imp__InitializeCriticalSection */
extern void (__stdcall *w29c_ecsP)(void *a);  /* _w29c_ecsP -> __imp__EnterCriticalSection */
extern char w29c_ltab[];                      /* _w29c_ltab -> __crtheap+0x4 */

struct w29c_hslot { char pad[8]; volatile int inUse; char cs[0x18]; };  /* 36 B */

void lockfhandle_q(int fh)
{
    volatile struct w29c_hslot **grp;
    struct w29c_hslot *p;
    int idx;
    int bit;

    idx = (fh & ~0x18) >> 3;
    bit = (fh & 0x1f) << 2;
    grp = (volatile struct w29c_hslot **)(w29c_ltab + idx);
    p = (struct w29c_hslot *)((char *)grp[0] + bit * 9);
    if (p->inUse == 0) {
        w29c_lockX(0x11);
        if (p->inUse == 0) {
            w29c_icsP(&p->cs);
            ++p->inUse;
        }
        w29c_unlockX(0x11);
    }
    w29c_ecsP((char *)grp[0] + bit * 9 + 0xc);
}