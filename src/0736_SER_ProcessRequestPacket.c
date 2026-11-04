/* w41E_905c0_v1: 96-B chunk @ 0x905c0 (VA 0x4905c0),
 * public ?SER_ProcessRequestPacket@@YAXAAUSERIAL_PACKET_WRAPPER@@@Z
 * (def-side map below; caller stubs reference the mangled name).
 * FA body: gate cmp [mpInfo+0x164]^1 vs (uchar)[w+0x23]; equal fallthrough
 * -> retrieveFromQueueq(&HistoryQueue, *(long*)(w+4), Ctrl+0x12e);
 *    setPacketInfo(Ctrl+0x146, *(long*)(w+4), 2);
 *    *(char*)(Ctrl+0x128) = 1; exit A.  jne-not-equal -> B: Ctrl+0x12a = 1.
 * All 6 abs dwords in FA carry HIGHLOW fixups (mpread + 2 push args +
 * the HQ push + the 2 c6-store imms at 0x41/0x4a) -> mapped interior
 * externs give CL's own HIGHLOWs.
 */
extern long w41e_mpon;
/* map _w41e_mpon=?mpInfo@@3UMP_INFO@@C+0x164 */
extern unsigned char w41e_hq[0x100];
/* map _w41e_hq=?HistoryQueue@@3USERIAL_QUEUE@@A */
extern unsigned char w41e_ctlInQ[0x20];
/* map _w41e_ctlInQ=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12e */
extern unsigned char w41e_ctlPkt[0x20];
/* map _w41e_ctlPkt=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x146 */
extern unsigned char w41e_f128;
/* map _w41e_f128=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x128 */
extern unsigned char w41e_f12a;
/* map _w41e_f12a=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12a */

void __cdecl retrieveFromQueueq(void *q, long l, void *out);
void __cdecl setPacketInfo(void *pk, long a, long b);

void __cdecl w41e_serprq(void *w)
{
    if (*(unsigned char *)((char *)w + 0x23) == (w41e_mpon ^ 1)) {
        retrieveFromQueueq(w41e_hq, *(long *)((char *)w + 4), w41e_ctlInQ);
        setPacketInfo(w41e_ctlPkt, *(long *)((char *)w + 4), 2);
        w41e_f128 = 1;
    } else {
        w41e_f12a = 1;
    }
}