/* rva 0x2300 (8960), 32 B - zero player_list+0x18 then
   net_add_player_id(0x51c288, st, 0). */
typedef struct _socket_state socket_state;

extern void net_add_player_id(char *, socket_state *, int);
extern unsigned long w34b_pl;
extern char w34b_pp[];

void w34b_2300(socket_state *st)
{
    w34b_pl = 0;
    net_add_player_id(w34b_pp, st, 0);
}