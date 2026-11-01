// __mtterm @ rva 0xd9100 (33 B) — mtdeletelocks, then if the TLS index
// (dword at _ctype+0x3b0, getmbcp-style baked-addend moffs) != -1,
// TlsFree(idx) off the IAT and idx = -1 (c7 05).
// C adds a dead push/pop ebx around a dllimport call whose argument is a
// memory load (w11a_q4-q6; plain stdcall extern w11a_q7 is clean but
// binds the wrong symbol class) — naked asm escape (w11a_11_mt2,
// byte-exact); imp-array extern + map _impTlsFree=__imp__TlsFree.
extern void __cdecl _mtdeletelocks(void);
extern unsigned char _ctype[];
extern void *impTlsFree[];

void __declspec(naked) __cdecl _mtterm_q(void)
{
    __asm
    {
        call _mtdeletelocks
        mov eax, dword ptr [_ctype + 0x3b0]
        cmp eax, -1
        je Lret
        push eax
        call dword ptr [impTlsFree]
        mov dword ptr [_ctype + 0x3b0], -1
    Lret:
        ret
    }
}