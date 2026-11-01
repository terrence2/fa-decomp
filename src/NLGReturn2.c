// __NLG_Return2 @ rva 0xd492a (16 B, gap chunk — no FPO record) — the NLG
// return trampoline: eb c3 SHORT jmp into __local_unwind2+0x1d (0x4d48ef),
// then a full unwind-exit epilogue (pop fs:[0] / add esp,0xc / pop edi /
// pop esi / pop ebx / ret) reached only by fall-in from __local_unwind2's
// own tail. FA's eb is a 2-byte short jmp with the rel8 (-0x3d) baked —
// no relocation carries it — and MASM's `jmp extern` is always e9 (5 B),
// which would shift the tail 3 B. Escape: bake the SHORT jmp with _emit
// (chunk VAs are link-fixed), probe w16b_6b exact incl. the 64 8f 05
// pop-fs:[0] disp32 (no reloc, stays 0).
int __declspec(naked) _NLG_Return2(void)
{
    __asm {
        _emit 0xeb          ; jmp short __local_unwind2+0x1d (0x4d48ef)
        _emit 0xc3          ; rel8 = -0x3d
        pop dword ptr fs:[0]
        add esp, 0xc
        pop edi
        pop esi
        pop ebx
        ret
    }
}