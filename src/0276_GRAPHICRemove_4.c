// @GRAPHICRemove@4 @ rva 0x423c0 (64 B) — FA asm: push esi / eax=graphics,
//   edx=1 / loop: mov si,[curId] / cmp [eax+4],si / jne skip / test [eax+2],dx
//   / je skip / mov [eax+4],0xffff / skip: add eax,0x66 / cmp eax,noMixLeft /
//   jb loop / mov eax,[thisComputer] / cmp eax,ecx / jne / call MPGraphicRemove
//   / pop esi / ret. Fastcall GRAPHICRemove(this). Plain C: do-while over the
//   graphics MODSPEC array (GRAPHICUpdate twin — same noMixLeftArr bound); the
//   16-bit test-in-reg gives mov edx,1/test dx (family tell); curId/f reload
//   per iteration because CL can't prove the 0xffff store doesn't alias them;
//   the a1-first cmp eax,ecx tail came out of plain C here (ecx is the fastcall
//   param), no naked escape needed (wave-19 two-global-compare tell avoided).
extern char graphics[];
extern char noMixLeftArr[];   // -> ?noMixLeft@@3UMODSPEC@@A
extern unsigned short curId;
extern long thisComputer;
extern void __stdcall MPGraphicRemoveX(void);

void __fastcall GRAPHICRemove_q(long this_)
{
    unsigned long m = (unsigned long)graphics;
    unsigned short f = 1;
    do {
        if (curId == *(unsigned short *)(m + 4)
            && (*(unsigned short *)(m + 2) & f))
            *(unsigned short *)(m + 4) = 0xFFFF;
        m += 0x66;
    } while (m < (unsigned long)noMixLeftArr);
    if (thisComputer == this_)
        MPGraphicRemoveX();
}