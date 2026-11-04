/* probe w45D_4b460 (FA 0x44b460, 128B): SER_WriteAvail OutQueue space calc */
extern unsigned char w45D_crb[];       /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */
extern unsigned char w45D_opb[];       /* ?OutPacket@@3USERIAL_PACKET_WRAPPER@@A */
extern unsigned char w45D_oqb[];       /* ?OutQueue@@3USERIAL_QUEUE@@A (VA 0x5680b8) */
void w45D_enter(void);                 /* ?SER_EnterCriticalCodeForeground@@YAXXZ */
void w45D_leave(void);                 /* ?SER_LeaveCriticalCodeForeground@@YAXXZ */

long __cdecl w45D_4b460(long unused)
{
    long r, q;
    if (w45D_crb[0x12d] == 0)
        return 0;
    q = 0x14 - *(long *)(w45D_opb + 0x14);
    w45D_enter();
    if (*(long *)(w45D_oqb + 4) > *(long *)(w45D_oqb + 0)) {
        r = (*(long *)(w45D_oqb + 4) - *(long *)(w45D_oqb + 0)
             - *(long *)(w45D_oqb + 8)) * 4 + 0xfc;
    } else {
        r = (*(long *)(w45D_oqb + 4) - *(long *)(w45D_oqb + 0)) * 4 + 0xfc;
    }
    w45D_leave();
    return r * 5 + q;
}