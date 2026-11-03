/* chunk ?SER_SendHoldingBuffer@@YAXXZ @ rva 0xa9090 (dec 692368, 64 B)
 * void __cdecl: if (!Ctrl.b@0x12d) return;
 * if (ser_rs232_putpacket([Ctrl+0x234], [Ctrl+0x26], Ctrl+0x2a)) {
 *     *(unsigned long*)(mpInfo+0x14c) = 1; SER_ShutdownLowLevel(); }
 * NOTE dis.py elided the c7 05 store before the tail jmp (raw-verified).
 */
extern char w31g_cb;    /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12d */
extern unsigned long w31g_b234;   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */
extern unsigned long w31g_d26;    /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x26 */
extern char w31g_p2a;             /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x2a */
extern unsigned long w31g_mpi;    /* ?mpInfo@@3UMP_INFO@@C+0x14c */
extern int __stdcall w31g_rsput(void *, unsigned long, char *);
extern void __cdecl w31g_sdl(void);

void __cdecl w31g_sendhold(void)
{
    if (!w31g_cb)
        return;
    if (w31g_rsput(&w31g_b234, w31g_d26, &w31g_p2a)) {
        w31g_mpi = 1;
        w31g_sdl();
    }
}
