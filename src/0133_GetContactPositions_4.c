// @GetContactPositions@4 @ rva 0x14240 = 82496, 96 B (fastcall 1 arg (obj
//   ptr array) -> esi; regs edi=i, esi=o, ebx=pd; FA loop bottom cmp is
//   reg-left cmp edi,eax / jl; CPGetContact is __stdcall (FA callee does
//   ret 0x4 — call site push edi; call; with NO stack cleanup).
// v4 (EXACT recipe): unsigned short c + __stdcall CPGetContactQ(long)
//   extern — CL emits and eax,0xffff and drops the add esp,4.  Patched
//   window 75,4 (0x4b..0x4e): FA's loop bottom is reg-left cmp edi,eax /
//   jl (3b f8 7c) while CL emits the freshly-loaded global left (3b c7
//   7f) — orientation is spelling-independent (g8 test); opcode+modrm+jcc
//   only, no reloc sites (the a1 disp32 at 0x46 sits before the window).
extern int w26_numContactsQ; /* map _w26_numContactsQ=?numContacts@@3JA */
extern void *w26_objPtrsQ[]; /* map _w26_objPtrsQ=_objPtrs */
extern short __stdcall CPGetContactQ(long n); /* map _CPGetContactQ@4=?CPGetContact@@YGGJ@Z */
extern int __stdcall GRTo2dQ(unsigned int id, void *dst); /* map _GRTo2dQ@8=_GRTo2d@8 */

void __fastcall w26c_GetContactPositions_q(unsigned int *o)
{
    int i;
    unsigned short c;
    unsigned int *pd;
    for (i = 0; i < w26_numContactsQ; i++) {
        c = CPGetContactQ(i);
        if (c == 0) {
            *(unsigned short *)&o[i] = 0x8000;
            continue;
        }
        pd = (unsigned int *)&o[i];
        if (GRTo2dQ((unsigned int)w26_objPtrsQ[c] + 0x11, pd))
            *(unsigned short *)pd = 0x8000;
    }
}/* patch 75,4,3bf87cc1 */
