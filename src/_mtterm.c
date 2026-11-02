// __mtterm @ rva 0xd9100 (889088, 33 B) — _mtdeletelocks() first, then if
//   the TLS index (dword at _ctype+0x3b0, getmbcp-style baked-addend
//   moffs) != -1: push idx, call TlsFree off the IAT (ff 15), and store -1
//   (c7 05 imm32). Naked-asm escape: the early-wave note blamed the
//   dllimport-call dead-ebx wrap; that wall never fires here — the real
//   miss in early probes was the missing _mtdeletelocks CALL.
// EXACT as plain C (survey tier-1 probe v2): __declspec(dllimport) TlsFree
//   decl (ff 15 with no ebx bookends because the argument is idx, a
//   register-resident local), _mtdeletelocks() in statement position before
//   the moffs read. v1 (no _mtdeletelocks call — structurally wrong read of
//   FA) failed on the leading e8. Maps VERBATIM: _impTlsFree=__imp__TlsFree
//   (becomes vestigial — the dllimport decl emits __imp__TlsFree directly;
//   keep or drop at merge, no FROM references remain).

// probes: build/survey/probes/t1_mtterm_v1.c (no), t1_mtterm_v2.c (EXACT) —
//   run: python3 build/survey/hybrid_probe.py build/survey/probes/tier1_b2.json
__declspec(dllimport) int __stdcall TlsFree(unsigned long idx);
extern void __cdecl _mtdeletelocks(void);
extern unsigned char _ctype[];

void __cdecl _mtterm_q(void)
{
    long idx;
    _mtdeletelocks();
    idx = *(long *)((char *)_ctype + 0x3b0);
    if (idx != -1) {
        TlsFree((unsigned long)idx);
        *(long *)((char *)_ctype + 0x3b0) = -1;
    }
}