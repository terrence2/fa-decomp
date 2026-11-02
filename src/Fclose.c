// _fclose @ rva 0xd3f10 (63 B) — int fclose(FILE *f) CONVERTED as a
// 4-patch hybrid (band N1, 2026-11-02). Old walls: the _IOEOF mem byte
// test (CL emits mov al/test al pair, 2 insns over 5 B) and FA's rv=-1
// parked in edi at entry (CL computes rv on the success path instead).
// C form (v2): rv=-1 first-decl + the eof store as a dword write on the
// -1 path. Patches:
//   patch 2,0,bfffffffff — INSERT (0-len delete) mov edi,-1 before the
//     lock call (FA parks the -1; 5 B in).
//   patch 0xb,5,f6460c40 — load-folds-to-test: mov al,[esi+0xc]/test al,0x40
//     -> test byte [esi+0xc],0x40.
//   patch 0x10,1,0c — je short disp repair after the -3 B shift (dest =
//     EOF branch).
//   patch 0x11,15,c7460c000000008bc75f5ec3 — EOF-branch rewrite: FA stores
//     0 back to the flag dword then rv=edi/pop edi/pop esi/ret; CL had
//     loaded-and-anded the flag (21->15 B).
// _lock_file/_fclose_lk/_unlock_file are FA chunk anchors (C spellings
// decorate straight onto __lock_file/__fclose_lk/__unlock_file — no maps). Probes: p_w23_Fclose_v1 plain-C failed;
// n1_Fclose_v1 (bf ff ff ff = 4 B) FATAL "unexplained tail"; v2 EXACT.
extern void __cdecl _lock_file(void *f);
extern int __cdecl _fclose_lk(void *f);
extern void __cdecl _unlock_file(void *f);

int __cdecl fclose(void *f)
{
    int rv = -1;
    if (*(unsigned char *)((char *)f + 0xc) & 0x40) {
        *(unsigned long *)((char *)f + 0xc) = 0;
        return rv;
    }
    _lock_file(f);
    rv = _fclose_lk(f);
    _unlock_file(f);
    return rv;
}