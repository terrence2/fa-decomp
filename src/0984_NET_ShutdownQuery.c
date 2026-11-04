// ?NET_ShutdownQuery@@YAXXZ @ rva 0xacf30 (48 B) — FA asm: a1 <socket_list
//   +0x418>/83 f8 ff (cmp eax,-1)/74 09 (skip close)/50/e8
//   ?socket_close@@YAXI@Z (CDECL — add esp,4)/6a 00 6a 00/e8
//   ?net_set_callback_host@@YAXPAXP6AX0W4PLAYER_ACTION@@PADPAUNET_ADDRESS@
//   @J@Z@Z (add esp,8)/6a 01/e8 ?net_set_often_state@@YAXW4PLAYER_STATE@@@Z
//   (add esp,4)/c3.  Closes the query socket handle (socket_list+0x418) if
//   not -1, then UNCONDITIONALLY nulls the host callback and sets
//   often-state 1 (both past the je skip target).  Plain C (mirror of
//   NET_CancelPlayerList's +0x420 band, cdecl socket_close).  Probe
//   build/w4probe/b20f_NET_ShutdownQuery.obj — exact modulo fixup dwords.
extern long sqSocket;   /* ?socket_list@@3USOCKET_STATE_LIST@@A+0x418 */

extern void __cdecl socket_close(unsigned h);
extern void __cdecl netSetCbHost(void *p, void *cb);
extern void __cdecl netSetOftenState(int st);

void NET_ShutdownQuery_q(void)
{
    if (sqSocket != -1)
        socket_close(sqSocket);
    netSetCbHost(0, 0);
    netSetOftenState(1);
}