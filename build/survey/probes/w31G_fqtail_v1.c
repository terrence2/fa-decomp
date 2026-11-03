/* chunk ?fetchFromQueueTail@@YAXAAUSERIAL_QUEUE@@AAUSERIAL_PACKET_WRAPPER@@@Z
 * @ rva 0x98500 (dec 623872, 80 B) — void __cdecl, packet-queue pop:
 * w = q->pkts[q->tail]; zero q->pkts[q->tail] (12 dwords);
 * ++q->count; q->tail = (q->tail + 1) % q->cap (cdq/idiv).
 * SERIAL_QUEUE: tail@4, cap@8, count@0x10, pkts@0x14 (ptr).
 * SERIAL_PACKET_WRAPPER: 12 dwords (48 B).
 */
typedef struct { long pad0; long tail; long cap; long pad8; long padc;
                 long count; struct W31G_SPW32 *pkts; } W31G_SQ;
typedef struct W31G_SPW32 { long d[12]; } W31G_SPW32;

void __cdecl w31g_fqtail(W31G_SQ *q, W31G_SPW32 *w)
{
    int i;
    *w = q->pkts[q->tail];
    for (i = 0; i < 12; i++)
        q->pkts[q->tail].d[i] = 0;
    q->count++;
    q->tail = (q->tail + 1) % q->cap;
}
