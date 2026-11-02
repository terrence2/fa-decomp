/* ?setPacketInfo@@YAXAAUSERIAL_PACKET@@JJ@Z @ rva 0x97fa0 (dec 622496),
 * size 0x20 — EXACT, pure C, no patches, no relocs.
 *
 * C recipe: FA's byte-stores to packet bytes 0 and 3 (| 0xFC mask on
 * byte 0) emit directly; byte 3 at pk+3 via a byte-index store.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_setPacketInfo_v1.obj 622496 \
 *   build/survey/probes/w24a_setPacketInfo_v1_fit.obj
 */
void setPacketInfo(void *pk, long a, long b)
{
    *(unsigned char *)pk = (unsigned char)b | 0xFC;
    ((unsigned char *)pk)[3] = (unsigned char)a;
}
