// __get_osfhandle @ rva 0xdec90 (74 B, FPO) — CRT fd -> OS handle CONVERTED
// as a 9-patch hybrid (band N1, 2026-11-02). The old tier0 wall: FA's
// fd->ecx bit-math register plan (idx in ecx, grp in eax, the FOPEN test as
// a direct 66-bit mem test f6 40 04 01 on the loaded row pointer) has no
// scratch save/restore for CL to find. C form (v9): idx ops FIRST (FA
// order: (fd&0x1f)<<2 then +8*8 in the o2 chain), grp=(fd & ~0x18)>>3 on
// the signed fd (sar), p = *(unsigned long *)((char *)&pioinfoX + blk),
// p += idx; the FOPEN test via *(unsigned char *)(p + 4) & 1; failure
// stores errno=9 via _errno, 0 via the dos-errno setter chunk, return -1.
// Patches (post-previous-patch offsets; delete syntax = 'OFF,OLDLEN,'):
//   4,1, — delete one redundant opcode byte
//   4,1,3b — cmp operand-order mirror (FA 3b 0d [nhandle] cmp ecx,[mem]
//     vs CL 39)
//   0xa,1,73 / 0xb,1,22 — jb polarity + and-opcode fixes after the mirror
//   0xc,14,8bc183e11fc1e10283e0e7c1f803 — FA's idx/grp register plan
//     (mov eax,ecx / and ecx,0x1f / shl ecx,2 / and eax,0xe7 / sar eax,3 /
//     test byte; 20->14 B)
//   0x1a,17,8d14c9 8b80000000 03c2 f6400401,5:6:_pioinfoX — lea edx,[ecx*8]
//     + mov eax,[pioinfo] (+ add eax,edx) + the direct f6 40 04 01 mem
//     bit-test that was the tier0 wall; DIR32 re-add _pioinfoX at site 5,
//     payload dword zero (20->17 B)
//   0x2a,1,03 — add-opcode fix in the errno path
//   0x2d,1, / 0x3e,1, — delete two 1-B duplicate bytes
// Probes: bm_get_osfhandle_v1..v8 KEEP-ASM at tier0; n1_get_osfhandle_v9
// EXACT.
extern unsigned long nhandleX;
extern char pioinfoX;
extern long *errnoX(void);
extern long *setDosErrnoX(void);

long get_osfhandle_q(int fd)
{
    unsigned long o2, blk, p;
    if ((unsigned long)fd >= nhandleX)
        goto fail;
    o2 = (unsigned long)(fd & 0x1f);
    o2 <<= 2;
    blk = (fd & ~0x18) >> 3;
    o2 = o2 + o2 * 8;
    p = *(unsigned long *)((char *)&pioinfoX + blk);
    p += o2;
    if (*(unsigned char *)(p + 4) & 1)
        return *(long *)p;
fail:
    *(long *)errnoX() = 9;
    *(long *)setDosErrnoX() = 0;
    return -1;
}