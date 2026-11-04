// ?NET_SlaveShutdown@@YAXXZ @ rva 0x1780 (48 B) — FA asm: call
//   ?socket_close_all@@YAXXZ / call ?net_free_player_list@@YAXXZ /
//   push0/push0/call ?net_set_callback_players@@... / add esp,8 /
//   push0/push0/call ?net_set_callback_connected@@... / add esp,8 / ret.
//   Plain C cdecl void(void); the callees are FA.SMS-mangled chunks so the
//   externs map to their mangled names (wave-13 rule).  Chunk itself is a
//   named mangled chunk, so the C fn carries the _q suffix.
extern void __cdecl socket_close_all(void);
extern void __cdecl net_free_player_list(void);
extern void __cdecl net_set_callback_players(void *a, void *b);
extern void __cdecl net_set_callback_connected(void *a, void *b);

void NetSlaveShutdown_q(void)
{
    socket_close_all();
    net_free_player_list();
    net_set_callback_players(0, 0);
    net_set_callback_connected(0, 0);
}