/* ?insertQueue@@YAXAAUSERIAL_QUEUE@@AAUSERIAL_PACKET_WRAPPER@@@Z @ rva
 * 0x98430 (96 B) — cdecl: j = w->[4]; idx = j % q->[8];
 * updateQueueHead(q, j); memcpy(q->[0x14] + idx*48, w, 0x30) (rep movsd,
 * 12 dwords); q->[0x14][...] marker dword +0x10 = 1 (table reloaded);
 * ++q->[0xc]; q->[0] = (idx+1) % q->[8]. */
extern void __cdecl w34E_uqh(void *q, long j);  /* =?updateQueueHead@@YAXAAUSERIAL_QUEUE@@J@Z */
extern void *memcpy(void *, const void *, unsigned);   /* intrinsic — no map */

typedef struct {
    long head;      /* +0x0 */
    long f4;        /* +0x4 */
    long cap;       /* +0x8 */
    long cnt;       /* +0xc */
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
    ++q->cnt;
    q->head = (idx + 1) % q->cap;
}