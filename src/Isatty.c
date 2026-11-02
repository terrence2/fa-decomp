// __isatty @ rva 0xdc5d0 (48 B) — CRT isatty CONVERTED as a 5-patch hybrid
// (band N1, 2026-11-02). C form: unsigned-handled range test
// `(unsigned long)fh >= (unsigned long)_nhandle => 0`, then idx=(fh&0x1f)<<2,
// grp=(fh&~0x18)>>3 (FA's sar-based signed grp over the shift pair), row =
// *(char **)((char *)fhLockBase + grp) (scale-1 load), return
// row[idx+4] & 0x40 (the FDEV byte test).
// Patches (offsets are post-previous-patch positions — the round-1 run at
// 0xf/0x11/0x13/0x16/0x1e was the FATAL that taught this):
//   patch 0: head 13->13B — CL loads fh into eax then cmp eax,_nhandle; FA
//     loads into EDX and mirrors 3b 15 [nhandle] (cmp edx,[mem]); DIR32
//     re-add _nhandle at site 6, payload dword zero.
//   patch 0x10,1,c2 / 0x11,3,83e21f / 0x14,0,c1e202 — FA's and edx,0x1f +
//     shl edx,2 idx-word math in edx (CL had the and-eax form and folded
//     the shift away).
//   patch 0x1d: tail 14->14B — FA's lea edx,[edx*8] + mov ecx,[mem+disp32]
//     + xor eax,eax + mov al,[ecx+edx+4] + and eax,0x40 vs CL's different
//     grp/index register plan; DIR32 re-add _fhLockBase at site 5, payload
//     dword zero.
// Probes: p_w23_Isatty_v1/_Gd/_G3 (flag axis) all failed; n1_Isatty_v1 EXACT.
extern long _nhandle;
extern char fhLockBase[];

int __cdecl _isatty(int fh)
{
    int idx, grp;
    char *row;
    if ((unsigned long)fh >= (unsigned long)_nhandle)
        return 0;
    idx = (fh & 0x1f) << 2;
    grp = (fh & ~0x18) >> 3;
    row = *(char **)((char *)fhLockBase + grp);
    return row[idx + 4] & 0x40;
}