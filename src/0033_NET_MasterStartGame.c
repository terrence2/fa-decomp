/* ?NET_MasterStartGame@@YADXZ @ rva 0xad20 (80 B; 67 code + 13 pad).
   char __cdecl(void): a1 [player_list dword0]; cmp eax,1; jg
   cont; xor al,al; ret; cont: calls scnps, $FA$_t_40b580, pkt(1,4,&pl),
   nso(3), napr->nsg, mov al,1; ret. */
extern void __cdecl w29c_scnpsX(void);   /* ?socket_close_non_player_sockets@@YAXXZ */
extern void __cdecl w29c_t40bX(void);    /* $FA$_t_40b580 */
extern char __cdecl w29c_pktX(short n, unsigned char c, void *pl);   /* ?pkt_send_player_info@@YADHGPAUNET_PLAYER_LIST@@@Z */
extern void __cdecl w29c_nsoX(int st);   /* ?net_set_often_state@@YAXW4PLAYER_STATE@@@Z */
extern char __cdecl w29c_naprX(void);    /* ?net_all_players_ready@@YADXZ */
extern void __cdecl w29c_nsgX(void);     /* ?net_start_game@@YAXXZ */
struct UNET_PLAYER_LIST { int playerCount; char pad[0x88]; };
extern struct UNET_PLAYER_LIST w29c_pl;  /* _w29c_pl -> ?player_list@@3UNET_PLAYER_LIST@@A */

char NETMasterStartGame_q(void)
{
    if (w29c_pl.playerCount <= 1)
        return 0;
    w29c_scnpsX();
    w29c_t40bX();
    w29c_pktX(1, 4, &w29c_pl);
    w29c_nsoX(3);
    if (w29c_naprX())
        w29c_nsgX();
    return 1;
}