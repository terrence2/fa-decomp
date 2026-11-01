// PutFakeKey @ rva 0x11c90 — decompiled from FA.EXE (probe d227_pfk7.c, byte-exact)
extern char waitCounter[];
extern char adCount[];
__declspec(naked) void __fastcall PutFakeKey_q(unsigned short a)
{
    __asm {
        mov ax, word ptr [waitCounter+4]
        cmp ax, 8
        jge fin
        movsx edx, ax
        inc ax
        mov word ptr [adCount + edx*2 + 8], cx
        mov word ptr [waitCounter+4], ax
        fin: ret
    }
}
