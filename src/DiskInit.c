// @DiskInit@0 @ rva 0xa9c80 (48 B) — FA asm (fastcall, 0 args): 33 c0/33 c9/
//   66 a3 <?openHandles@@3FA> (word store of ax)/66 a3 <_dosError>/
//   0f bf d0 (movsx edx,ax — store uses the PRE-inc index)/66 40 (inc ax)/
//   66 3d 10 00 (cmp ax,0x10, imm16 on ax)/89 0c 95 <?handles32@@3PAPAXA>
//   (base-less sib + disp32 store AFTER the cmp; store/branch share the
//   cmp flags — 89 0c 95 is flag-neutral)/7c ee (loop; the 66 a3 pair runs
//   once ahead of the loop)/33 c0/a2 <_readOnly>/a2 <_diskFull>/c3.  Naked-
//   asm escape: the movsx-of-old-index/inc/check/store order and the 66-ax
//   loop var cannot be expressed in C.  Probe build/w4probe/w19_diskinit_v1.obj
//   — exact.
extern unsigned short openHandles0;   /* ?openHandles@@3FA */
extern unsigned short dosError;       /* _dosError (identity) */
extern void *handles32G[];            /* ?handles32@@3PAPAXA */
extern char readOnly;                 /* _readOnly (identity) */
extern char diskFull;                 /* _diskFull (identity) */

__declspec(naked) void __fastcall DiskInit_f(void)
{
    __asm {
        xor eax, eax
        xor ecx, ecx
        mov openHandles0, ax
        mov dosError, ax
    Lp:
        movsx edx, ax
        inc ax
        cmp ax, 0x10
        mov handles32G[edx*4], ecx
        jl Lp
        xor eax, eax
        mov readOnly, al
        mov diskFull, al
        ret
    }
}