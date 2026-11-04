/* rva 0x92eb0 (80 B, __cdecl, 1 ptr arg): streamer method-table bootstrap.
 * Calls vtable[0] of *(*(p+4)) with (p, 0, 0x14) - the streamer object's
 * alloc/get entry (6a 14 / 6a 00 / push p / call [eax]) - and seeds the
 * returned table: r[0..0xc] = the four streamer entry points (chunks
 * 0x4931c0, 0x493480, 0x492f00, 0x4931a0, DIR32 sites on the $FA$ gap
 * anchors, transplanted as FA's c7 00/c7 40 imm forms via the patch
 * newsites), and the byte flags r[0x10]=0, r[0x11]=0, r[0x12]=1. The
 * vtable call's return goes to BOTH the seed stores and *(p+0x17e) (FA's
 * 89 86 7e010000).
 */
typedef void *(__cdecl *SVT0)(void *, long, long);

void __cdecl w44e_streamerInit(char *p)
{
    void **vtab = *(void **)(p + 4);
    SVT0 fn = ((SVT0 *)vtab)[0];
    void *rv = fn(p, 0, 0x14);
    *(void **)(p + 0x17e) = rv;
}