// __fclose_lk @ rva 0xd3f50 (95 B) — the locked half of fclose CONVERTED as
// a 1-patch hybrid (band N1, 2026-11-02). Old wall (tier0 byte-width):
// the 0x83 open-mode flag check must be a DIRECT mem byte test f6 46 0c 83;
// CL emits mov al,[esi+0xc]/cmp al,0x83 (5 B over the same span). C form
// unchanged from the v3 spelling (r=-1 first-decl, fd/t staged, the
// tmpfname free + dword clear deferred past the add esp,4 — all natural
// under /O2). One patch: rewrite 0xb 5 B -> f6 46 0c 83; the following jcc
// auto-reloc'd.
// Maps: _flush_lk=$FA$_t_4d5f30, _fcloseUnk2=$FA$_t_4d82a0 (unchanged),
// _close=__close (new anchor). Probes: p_FcloseLk_v1..v3 KEEP-ASM; v4 EXACT.
extern int __cdecl _flush_lk(void *f);
extern int __cdecl fcloseUnk2(void *f);
extern int __cdecl _close(int fd);
extern void __cdecl free(void *mem);

int __cdecl _fclose_lkQ(void *f)
{
    int r = -1;
    if (*(unsigned char *)((char *)f + 0xc) & 0x83) {
        int fd;
        void *t;
        r = _flush_lk(f);
        fcloseUnk2(f);
        fd = *(int *)((char *)f + 0x10);
        if (_close(fd) < 0)
            r = -1;
        else {
            t = *(void **)((char *)f + 0x1c);
            if (t) {
                free(t);
                *(int *)((char *)f + 0x1c) = 0;
            }
        }
    }
    *(int *)((char *)f + 0xc) = 0;
    return r;
}