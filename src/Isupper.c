// _isupper @ rva 0xd40d0 (45 B) — MBCS-gated ctype test. FA compares
// the MBCS flag (dword at _ctype+0x204, __mbcurmax) DIRECTLY in memory
// (cmp [mem],imm); CL 4.2 loads it into eax first (w16a_isalpha3/4/5 all
// emit a1+cmp eax), and FA's reg plan also differs from CL's (param in ecx,
// pctype ptr in edx, result zero-extended via xor eax,eax; CL picks
// eax/ecx) — naked asm escape (w16a_src_Isupper, byte-exact; [_ctype+disp]
// baked-addend moffs per _mtterm precedent).
extern unsigned char _ctype[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

void __declspec(naked) __cdecl isupper(void)
{
    __asm
    {
        cmp     dword ptr [_ctype + 0x204], 1
        jle     short TblPath
        mov     ecx, dword ptr [esp + 4]
        push    1
        push    ecx
        call    _isctype
        add     esp, 8
        ret
    TblPath:
        mov     edx, dword ptr [_pctype]
        xor     eax, eax
        mov     ecx, dword ptr [esp + 4]
        mov     ax, word ptr [edx + ecx*2]
        and     eax, 1
        ret
    }
}
