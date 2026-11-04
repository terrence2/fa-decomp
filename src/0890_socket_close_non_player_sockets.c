// 0xa2fb0 ?socket_close_non_player_sockets@@YAXXZ (64 B) — v1
extern char w28c_sockArr[];  /* ?socket_list@@3USOCKET_STATE_LIST@@A */
extern void __cdecl w28c_sockCloseX(unsigned long h);

void __cdecl w28c_sockCloseNPS(void)
{
    if (*(long *)(w28c_sockArr + 0x418) != -1L)
        w28c_sockCloseX(*(unsigned long *)(w28c_sockArr + 0x418));
    if (*(long *)(w28c_sockArr + 0x41c) != -1L)
        w28c_sockCloseX(*(unsigned long *)(w28c_sockArr + 0x41c));
    if (*(long *)(w28c_sockArr + 0x420) != -1L)
        w28c_sockCloseX(*(unsigned long *)(w28c_sockArr + 0x420));
}
