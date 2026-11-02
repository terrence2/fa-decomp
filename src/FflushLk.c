// __fflush_lk @ rva 0xd5ef0 (60 B) — int _fflush_lk(FILE *f) CONVERTED as a
// 2-patch hybrid (band N1, 2026-11-02). C form: flush via the $FA$_t_4d5f30
// helper (nonzero => return -1), then the _IOCOMMIT flag (byte [f+0xd],0x40
// — the mem byte-test family) gates _commit(fd), whose result goes through
// FA's borrow tail (cmp eax,1 / mov eax,0 / pop esi / adc eax,-1: "c < 1 ?
// 0 : -1" staged as the unsigned compare). Patches:
//   patch 0x19,5,f6460d40 — load-folds-to-test: mov al,[esi+0xd]/test al,0x40
//     -> test byte [esi+0xd],0x40.
//   patch 0x2e,10,b8000000005e83d0ffc3 — adc-borrow tail reorder: FA pops
//     esi BETWEEN mov eax,0 and adc eax,-1; CL keeps esi live past the adc
//     (10->10 B rewrite of the commit-fail return).
// _commit is the FA chunk anchor __commit. Probes: w16a_fflushlk1/2 naked
// asm; n1_FflushLk_v1 EXACT.
extern int __cdecl _flush_lk(void *f);
extern int __cdecl _commit(int fd);

int __cdecl _fflush_lk(void *f)
{
    int c;
    if (_flush_lk(f))
        return -1;
    if (*(unsigned char *)((char *)f + 0xd) & 0x40) {
        c = _commit(*(int *)((char *)f + 0x10));
        return (unsigned long)c < 1 ? 0 : -1;
    }
    return 0;
}