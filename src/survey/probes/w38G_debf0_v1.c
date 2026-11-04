/* w38G __free_osfhnd @ 0xdebf0 (145 B, FPO 2-reg) — v1: guard first
 * (FA: cmp [nhandle],fh; jbe fail), then idx (fh&0x1f)<<2, grp sar,
 * slot ptr kept (FA edi), entry = row + o2*9, FOPEN/−1/__aexit_rtn+8==1
 * tests, 0/1/2 SetStdHandle dispatch (no result check), entry[0] = −1,
 * return 0; fail = errno 9 + dos-errno-0 chunk, return −1. */
extern unsigned long w38g_nhl;                /* -> __nhandle */
extern char w38g_pio2[];                      /* -> __crtheap+0x4 */
extern unsigned long w38g_aex8;               /* -> __aexit_rtn+0x8 */
extern int *__cdecl w38g_ern(void);           /* -> __errno */
extern void __cdecl w38g_den(void);           /* -> $FA$_t_4d99c0 */
__declspec(dllimport) int __stdcall SetStdHandle(long, void *);

int __cdecl w38g_foh(int fh)
{
    unsigned long o2;
    unsigned long *slot;
    unsigned long row;
    if ((unsigned long)w38g_nhl <= (unsigned long)fh)
        goto fail;
    o2 = (unsigned long)(fh & 0x1f);
    o2 <<= 2;
    slot = (unsigned long *)((char *)&w38g_pio2 + ((fh & ~0x18) >> 3));
    row = *(unsigned long *)slot;
    row = row + o2 + o2 * 8;
    if (!(*(unsigned char *)(row + 4) & 1) || *(long *)row == -1
            || w38g_aex8 != 1)
        goto fail;
    if (fh == 0)
        SetStdHandle(0xfffffff6, 0);
    else if (fh == 1)
        SetStdHandle(0xfffffff5, 0);
    else if (fh == 2)
        SetStdHandle(0xfffffff4, 0);
    *(unsigned long *)(*(unsigned long *)slot + o2 + o2 * 8) = -1;
    return 0;
fail:
    *w38g_ern() = 9;
    w38g_den();
    return -1;
}