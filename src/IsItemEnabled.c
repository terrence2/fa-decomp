// IsItemEnabled @ rva 0xcc10 — decompiled from FA.EXE (probe d219_iie3.c, byte-exact)
extern int enableHelper(void);
__declspec(naked) char __fastcall IsItemEnabled_q(short a)
{
    __asm {
        call enableHelper
        test byte ptr [eax+0x10], 2
        sete cl
        mov al, cl
        ret
    }
}
