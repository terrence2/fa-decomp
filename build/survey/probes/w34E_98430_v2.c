/* ?insertQueue@@... v2 — tbl field at +0x14 (extra +0x10 dword), and the
 * (idx+1) computation hoisted before the count load (C order head-first,
 * cnt second). */
extern void __cdecl w34E_uqh(void *q, long j);  /* =?updateQueueHead@@YAXAAUSERIAL_QUEUE@@J@Z */
extern void *memcpy(void *, const void *, unsigned);   /* intrinsic — no map */

typedef struct {
    long head;      /* +0x0 */
    long f4;        /* +0x4 */
    long cap;       /* +0x8 */
    long cnt;       /* +0xc */
    long f10;       /* +0x10 */
    char *tbl;      /* +0x14 */
} SQ;

typedef struct {
    long f0;        /* +0x0 */
    long idx;       /* +0x4 */
} SPW;

void __cdecl insertQueue(SQ *q, SPW *w)
{
    long j = w->idx;
    long idx = j % q->cap;

    w34E_uqh(q, j);
    memcpy(q->tbl + (idx << 4) * 3, w, 0x30);
    *(long *)(q->tbl + (idx << 4) * 3 + 0x10) = 1;
    q->head = (idx + 1) % q->cap;
    ++q->cnt;
}