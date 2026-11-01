// _ispunct @ rva 0xd41d0 (45 B, FPO fpo/esp params=1) — CRT locale ctype
// test, mask 0x10. Same band as wave-16's 11 is* locale lookups (Isalpha.c
// form): FA tests the MBCS flag (dword at __ctype+0x204, __mbcurmax)
// DIRECTLY in memory (83 3d <moffs> .. 01, MASM-only cmp [extern],imm) and
// uses a reg plan CL never picks (param in ecx, pctype ptr in edx, result
// zero-extended via xor eax,eax + 16-bit load) — naked asm escape.
extern unsigned char _ctype[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

void __declspec(naked) __cdecl ispunct(void)
{
    __asm
    {
        cmp     dword ptr [_ctype + 0x204], 1
        jle     short TblPath
        mov     ecx, dword ptr [esp + 4]
        push    0x10
        push    ecx
        call    _isctype
        add     esp, 8
        ret
    TblPath:
        mov     edx, dword ptr [_pctype]
        xor     eax, eax
        mov     ecx, dword ptr [esp + 4]
        mov     ax, word ptr [edx + ecx*2]
        and     eax, 0x10
        ret
    }
}