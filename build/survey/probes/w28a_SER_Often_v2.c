/* v2: volatile mstate forces FA's pair of a1 reloads (v1 folded to one). */
extern void __stdcall w28a_gp(void *ctl, int mode, void *buf);
    /* =_ser_rs232_getpacket@12 */
extern volatile unsigned long w28a_mstate;   /* =?mpInfo@@3UMP_INFO@@C+0x16c */
extern void *w28a_ctlG;                /* =?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */

void __cdecl w28a_SER_Often(void)
{
    unsigned char msg[4];
    if (w28a_mstate == 3 || w28a_mstate == 2)
        w28a_gp(w28a_ctlG, 0, msg + 3);
}
