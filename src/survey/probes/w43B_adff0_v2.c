// ?net_send_all@@ v2 — null test spelled `pkt == 0` hoping for FA's
// test esi,esi (85 f6; v1 gave cmp esi,edi).
extern long w43b_plc;    /* _w43b_plc=?player_list@@3UNET_PLAYER_LIST@@A+4 */
extern long w43b_my;     /* _w43b_my=?player_list@@3UNET_PLAYER_LIST@@A+0x14 */
extern long w43b_pl[];   /* _w43b_pl=?player_list@@3UNET_PLAYER_LIST@@A+0x66 */
extern char __cdecl w43b_pkt(void *pkt, long i);   /* _w43b_pkt=?pkt_send@@YADPAUNET_PKT@@H@Z */
extern void __cdecl w43b_ssd(unsigned long s);     /* _w43b_ssd=?socket_set_doa@@YAXI@Z */

void __cdecl w43b_nsa2(void *pkt)
{
    long i;
    long pl;

    i = 0;
    if (pkt == 0)
        return;
    if (w43b_plc <= 0)
        return;
    while (i < w43b_plc) {
        if (i != w43b_my) {
            pl = w43b_pl[i];
            if (pl != 0 && *(char *)(pl + 0x36) != 0) {
                if (w43b_pkt(pkt, i) == 0) {
                    pl = w43b_pl[i];
                    w43b_ssd(*(unsigned long *)pl);
                }
            }
        }
        i++;
    }
}