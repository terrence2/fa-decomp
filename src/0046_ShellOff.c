/* w45F ?ShellOff@@YGXXZ @ 0x40c010 (128 B, FPO 0 params, tail 8bff+8da4) — v2
 * v1 was byte-perfect through 0x6c — v1's only bug: I omitted the ms8=NULL
 * store (dis.py elided it) — FA stores both ms4 and ms8 to NULL.
 * FA: PushShellAlloc(); if (savePointer) ShellHideMouse();
 *   if (ms4) { MMFreePtr(ms4); ms4 = NULL; }
 *   if (ms8) { memmove(_curPalette, ms8, 0x300); MMFreePtr(ms8); ms8 = NULL; }
 *   MMFreeHandle(savePointer); savePointer = NULL;
 *   e9 jmp ?PopShellAlloc@@YGXXZ  (CL 4.2 emits the tail-jmp naturally!).
 * tail 9 B (8bff + 8da42400000000) not census: patch-appended. */
extern void __stdcall PushShellAllocA(void);   /* _PushShellAllocA@0 */
extern void __stdcall ShellHideMouseA(void);   /* _ShellHideMouseA@0 */
extern void __stdcall PopShellAllocA(void);    /* _PopShellAllocA@0 */
extern void * __fastcall MMFreePtrA(void *);   /* @MMFreePtrA@4 */
extern void * __fastcall MMFreeHandleA(void *);/* @MMFreeHandleA@4 */
extern void * __cdecl memmove_(void *, const void *, unsigned long); /* _memmove_=_memmove */
extern void * w45f_sp;                     /* _w45f_sp=?savePointer@@3PAUT_HANDLE@@A */
extern void * w45f_ms4;                    /* _w45f_ms4=?mouseShown@@3FA+0x4 */
extern void * w45f_ms8;                    /* _w45f_ms8=?mouseShown@@3FA+0x8 */
extern char w45f_pal;                      /* _w45f_pal=_curPalette */

void __stdcall w45F_ShellOff(void)
{
    PushShellAllocA();
    if (w45f_sp)
        ShellHideMouseA();
    if (w45f_ms4) {
        MMFreePtrA(w45f_ms4);
        w45f_ms4 = 0;
    }
    if (w45f_ms8) {
        memmove_(&w45f_pal, w45f_ms8, 0x300);
        MMFreePtrA(w45f_ms8);
        w45f_ms8 = 0;
    }
    MMFreeHandleA(w45f_sp);
    w45f_sp = 0;
    PopShellAllocA();
}