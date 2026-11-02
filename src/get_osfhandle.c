// __get_osfhandle @ rva 0xdec90 (74 B, FPO fpo/esp params=1) — CRT fd ->
// OS handle: bounds-check fd against [__nhandle] (3b 0d mem compare),
// then index the __pioinfo table (__crtheap+0x4; 8b 80 = [eax+disp32],
// no sib — symbol[reg] spelling per wave-19) with the fd/32*4 block
// index and fd&~0x18/8 row, test the FOPEN flag bit at +4, return
// [eax] (the osfhnd); failure calls __errno (stores EBADF=9) and the
// dos-errno setter chunk (stores 0) and returns -1. Naked asm (the
// fd->ecx bit-math register plan with no scratch save/restore).
extern void *nhandleX;
extern void *pioinfoX;
extern void *errnoX(void);
extern void *setDosErrnoX(void);

void __declspec(naked) get_osfhandle_q(void)
{
    __asm {
        mov  ecx, dword ptr [esp+4]
        cmp  ecx, dword ptr [nhandleX]
        jae  Lfail
        mov  eax, ecx
        and  ecx, 0x1f
        shl  ecx, 2
        and  eax, -25
        sar  eax, 3
        lea  edx, dword ptr [ecx+ecx*8]
        mov  eax, dword ptr pioinfoX[eax]
        add  eax, edx
        test byte ptr [eax+4], 1
        je   Lfail
        mov  eax, dword ptr [eax]
        ret
    Lfail:
        call errnoX
        mov  dword ptr [eax], 9
        call setDosErrnoX
        mov  dword ptr [eax], 0
        mov  eax, -1
        ret
    }
}