/* ?SER_Often@@YAXXZ @ rva 0x4b7d0 (48 B) — cdecl void(void):
   local dword; if (mpState==3 || mpState==2) getpacket(ctrl+0x234, 0, loc+3). */
extern void __stdcall w28a_gp(void *ctl, int mode, void *buf);
    /* =_ser_rs232_getpacket@12 */
extern unsigned long w28a_mstate;      /* =?mpInfo@@3UMP_INFO@@C+0x16c */
extern void *w28a_ctlG;                /* =?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */

void __cdecl w28a_SER_Often(void)
{
    unsigned char msg[4];
    if (w28a_mstate == 3 || w28a_mstate == 2)
        w28a_gp(w28a_ctlG, 0, msg + 3);
}
