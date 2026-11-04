/* v3: v2 struct fixed (count@0x10, pkts@0x14) + tail-assign before count++ */
typedef struct { long pad0; long tail; long cap; long padc; long count;
                 struct W31G_SPW32 *pkts; } W31G_SQ;
typedef struct W31G_SPW32 { long d[12]; } W31G_SPW32;
extern void *memcpy(void *, const void *, unsigned);
extern void *memset(void *, int, unsigned);

void __cdecl w31g_fqtail(W31G_SQ *q, W31G_SPW32 *w)
{
    memcpy(w, q->pkts + q->tail, 48);
    memset(q->pkts + q->tail, 0, 48);
    q->tail = (q->tail + 1) % q->cap;
    q->count++;
}
