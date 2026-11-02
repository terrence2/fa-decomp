// ?net_test_process_pkt@@YAXPAUNET_PKT@@H@Z @ rva 0x69dc0 (64 B) —
// void __cdecl(void *pkt, int idx).
// FA: 8b 44 24 04 / 56 / 8b 48 08 / f6 c1 01 / 74 25 / 8b 74 24 0c / 6a 12 /
// 56 / e8 [?pkt_send_type@@YADHH@Z] / 83 c4 08 / 84 c0 / 75 12 / 8b 04 b5
// [?player_list@@3UNET_PLAYER_LIST@@A+0x66] / 8b 08 / 51 / e8
// [?socket_close@@YAXI@Z] / 83 c4 04 / 5e / c3.
// NOTE: push order 0x12 first, then idx => C arg list (idx, 0x12).
typedef unsigned long ul;

extern void *w29d_plA[];                  /* ?player_list@@3UNET_PLAYER_LIST@@A+0x66 */
extern char __cdecl w29d_pst(int a, int b);   /* ?pkt_send_type@@YADHH@Z */
extern void __cdecl w29d_sclose(ul h);    /* ?socket_close@@YAXI@Z */

void __cdecl w29d_ntp(void *pkt, int idx)
{
    if (*(ul *)((char *)pkt + 8) & 1) {
        if (!w29d_pst(idx, 0x12)) {
            w29d_sclose(*(ul *)w29d_plA[idx]);
        }
    }
}