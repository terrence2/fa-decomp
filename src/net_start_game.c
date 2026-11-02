// ?net_start_game@@YAXXZ @ rva 0xae9a0 (48 B) — void net_start_game(void):
// socket_set_all_players_state_funcs(game_event_handler, 1, *(void *)
// &player_list) (a1 moffs value load of the first dword of the global
// UNET_PLAYER_LIST struct), then a 0-arg call of the unnamed chunk parked
// at $FA$_t_4ae9d0, then net_set_often_state((PLAYER_STATE)8). __cdecl
// caller-cleans add esp,0xc / add esp,4. Plain-C probe.
extern void ssapfQ(void *fn, int state, void *list);    /* socket_set_all_players_state_funcs */
extern void gameEventHandlerQ(void);                    /* the handler fn pushed by address */
extern void nsghQ(void);                                /* $FA$_t_4ae9d0 */
extern void nsofQ(int st);                              /* net_set_often_state */
extern void *playerListFirst;                           /* first dword of ?player_list@@3UNET_PLAYER_LIST@@A */

void net_start_game_q(void)
{
    ssapfQ(gameEventHandlerQ, 1, playerListFirst);
    nsghQ();
    nsofQ(8);
}