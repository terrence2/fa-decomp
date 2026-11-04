/* wave37D SER_ReadAvail 0x4b650 (80 B) v1 */
extern unsigned char w37d_serGate;   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12d */
extern long w37d_inLen;              /* ?InPacket@@3USERIAL_PACKET_WRAPPER@@A+0x14 */
extern long w37d_ctrlTail;           /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x198 */
extern long w37d_ctrlHead;           /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x19c */
void w37d_serEnter(void);            /* ?SER_EnterCriticalCodeForeground@@YAXXZ */
void w37d_serLeave(void);            /* ?SER_LeaveCriticalCodeForeground@@YAXXZ */
long SER_ReadAvail(long a, long b, long c)
{
    long x, d;
    if (w37d_serGate == 0)
        return 0;
    x = 0x14 - w37d_inLen;
    w37d_serEnter();
    d = w37d_ctrlHead - w37d_ctrlTail;
    w37d_serLeave();
    x += (d << 2) * 5;
    if (x > b)
        x = b;
    return x;
}
