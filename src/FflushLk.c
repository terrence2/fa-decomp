// __fflush_lk @ rva 0xd5ef0 (60 B) — int _fflush_lk(FILE *f): flush the
// stream buffer via the helper parked at $FA$_t_4d5f30 (0/-1); nonzero =>
// EOF (the je skips over mov eax,-1/pop/ret into the commit test). Then the _IOCOMMIT flag (0x4000, tested as BYTE [f+0xd],0x40 — mem
// byte test; CL emits mov al/test al, w16a_fflushlk1/2): _commit(fd) whose
// result goes through FA's borrow tail (cmp eax,1 / mov eax,0 / pop esi /
// adc eax,-1 — the pop esi interleaved BETWEEN mov and adc, byte-exact only
// in asm; probe w16a_fflushlk1 also puts pop after adc). No flag => xor
// eax,eax exit. Naked asm escape (w16a_src_FflushLk, byte-exact).
extern int __cdecl _flush_lk(void *f);
extern int __cdecl _commit(int fd);

void __declspec(naked) __cdecl _fflush_lk(void)
{
    __asm
    {
        push    esi
        mov     esi, dword ptr [esp + 8]
        push    esi
        call    _flush_lk
        add     esp, 4
        test    eax, eax
        je      short CommitChk
        mov     eax, -1
        pop     esi
        ret
    CommitChk:
        test    byte ptr [esi + 0xd], 0x40
        je      short ZeroRet
        mov     eax, dword ptr [esi + 0x10]
        push    eax
        call    _commit
        add     esp, 4
        cmp     eax, 1
        mov     eax, 0
        pop     esi
        adc     eax, -1
        ret
    ZeroRet:
        xor     eax, eax
        pop     esi
        ret
    }
}
