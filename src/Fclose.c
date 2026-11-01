// _fclose @ rva 0xd3f10 (63 B) — int _fclose(FILE *f): the _IOEOF reentry
// guard first (test BYTE [f+0xc],0x40 — mem byte test; CL emits mov al/test
// al, w16a_fclose1) → clear the flag dword and return EOF (-1, the rv=-1
// value kept in edi across the block); otherwise lock, __fclose_lk (r back
// through edi), unlock, return. Naked asm escape (w16a_src_Fclose,
// byte-exact).
extern void __cdecl _lock_file(void *f);
extern int __cdecl _fclose_lk(void *f);
extern void __cdecl _unlock_file(void *f);

void __declspec(naked) __cdecl fclose(void)
{
    __asm
    {
        push    esi
        push    edi
        mov     edi, -1
        mov     esi, dword ptr [esp + 0xc]
        test    byte ptr [esi + 0xc], 0x40
        je      short LockPath
        mov     dword ptr [esi + 0xc], 0
        mov     eax, edi
        pop     edi
        pop     esi
        ret
    LockPath:
        push    esi
        call    _lock_file
        add     esp, 4
        push    esi
        call    _fclose_lk
        add     esp, 4
        mov     edi, eax
        push    esi
        call    _unlock_file
        add     esp, 4
        mov     eax, edi
        pop     edi
        pop     esi
        ret
    }
}
