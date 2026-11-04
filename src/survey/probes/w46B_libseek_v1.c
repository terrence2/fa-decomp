/* w46B_libseek_v1 - _LibSeek@8, FA rva 0x78f60 (495456), 160 B, tail 8d9b... (6 B census pad)
 *
 * stdcall LibSeek(long recIdx, long pos) — FPO esp, cbRegs=3 (ebx/esi/edi), locals=0.
 * recIdx LOW WORD validated 1..10 (dec si; js/cmp si,0xa). 12-B records at
 * ?libAccess@@3PAULIBACCESS@@A+4 (f0@+0, f4cur@+4); record data ptr = libAccess[idx] (*4).
 * MMLock/MMLock fastcall; record byte-position math: dp = recPtr + f0*35
 * (shl3 -1 =>*7, lea *4+ => *35), limits @dp+0x1b / dp+0x1f, cur = rec.f4 + limit1.
 * Success stores arg2 (pos) into rec.f4cur and returns it; out-of-range returns 0.
 *
 * FA .reloc abs sites: 13 (errstr hintHndl+0xec), 28 (libAccess), 38 (errstr hintHndl+0xbc),
 * 48 (hintHndl), 53 (libAccess+4), 59 (libAccess+8), 6b (hintHndl), 91 (libAccess+8).
 * rel32 disp sites: 18 (ErrorExit), 3d (ErrorExit), 4d (MMLock), 7a (MMUnlock).
 * NOTE: whole-chunk transplant (FA bytes); husk documents semantics.
 */
extern void ErrorExit(char *msg);                       /* _ErrorExit */
extern void __fastcall MMLock(void *h, long mode);      /* @MMLock@8 */
extern void __fastcall MMUnlock(void *h);               /* @MMUnlock@4 */
extern unsigned char libRecArr[];                                 /* ?libAccess@@3PAULIBACCESS@@A at 0x542ba0 */

long __stdcall LibSeek(long recIdx, long pos)
{
    short u;
    long p0, rec, m0, dp, lim1, cur;
    u = (short)recIdx - 1;
    if (u < 0 || u >= 10)
        ErrorExit((char *)(libRecArr + 0x270));     /* 0x4f4010 = hintHndl-ish string */
    rec = ((long)u) * 3;
    p0 = *(long *)((char *)libRecArr + 4 * u);      /* libAccess[u] record data ptr */
    rec = rec * 4;                                   /* 12-B stride */
    if (!p0)
        ErrorExit((char *)(libRecArr + 0xbc));      /* err string 2 */
    MMLock(libRecArr, 0);
    m0 = *(long *)(libRecArr + 4 + rec);            /* records[u].f0 */
    cur = *(long *)(libRecArr + 8 + rec);           /* records[u].f4cur */
    dp = p0 + m0 * 35;
    lim1 = *(long *)(dp + 0x1b);
    cur += lim1;
    lim1 += *(long *)(dp + 0x1f);
    MMUnlock(libRecArr);
    if (cur >= lim1)
        return 0;
    *(long *)(libRecArr + 8 + rec) = pos;
    return pos;
}