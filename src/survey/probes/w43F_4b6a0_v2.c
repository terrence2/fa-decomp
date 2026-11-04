/* w43F 0x4b6a0 v2: w43F_inLen declared volatile - every read real: cmp read
 * becomes a1+83 f8 (mov eax,moffs / cmp eax,0x14), the inLen=0 store becomes
 * c7 05 imm (volatile imm store), and the final index read reloads from
 * memory (8b 0d / 33 c0 / 8a 81) instead of reusing the tracked-0 register.
 */
extern long w43F_serRA(long a, long b);
extern char w43F_serFG(void *p);
extern char w43F_serGate;               /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12d */
extern volatile long w43F_inLen;        /* ?InPacket@@3USERIAL_PACKET_WRAPPER@@A+0x14 */
extern char w43F_inBuf[];               /* ?InPacket@@3USERIAL_PACKET_WRAPPER@@A+0x1c */
extern void *w43F_inPkt;                /* ?InPacket@@3USERIAL_PACKET_WRAPPER@@A */

long w43F_SerPeek(long n)
{
    long a;
    if (!w43F_serGate) return -1;
    a = w43F_serRA(n, 1);
    if (!a) return -1;
    if (w43F_inLen >= 0x14) {
        if (!w43F_serFG(&w43F_inPkt)) return -1;
        w43F_inLen = 0;
    }
    return (long)(unsigned char)w43F_inBuf[w43F_inLen];
}
