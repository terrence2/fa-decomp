/* w45H 0xaceb0 ?NET_Shutdown@@YAXXZ: teardown order (proto guard, ws branch,
   callbacks clear, MMFreeAllId(0x10), socket_list -1 stores) */
typedef unsigned long ulong;
typedef unsigned char uchar;
void *memset(void *, int, unsigned long);

typedef struct { char pad[0x288]; ulong x288; } TP;
extern TP tcp_proto;                       /* _tcp_proto = ?tcp_proto@@3UNET_PROTOCOL@@A */
extern char netws;                         /* _netws = ?ws@@3U_winsock_funcs@@A */
extern char mpInfo;                        /* _mpInfo = ?mpInfo@@3UMP_INFO@@C */
typedef struct { char pad[0x1c]; uchar started; } PL;
extern PL player_list;                     /* _player_list = ?player_list@@3UNET_PLAYER_LIST@@A */
typedef struct { char pad[0x418]; long x418; long x41c; } SL;
extern SL socket_list;                     /* _socket_list = ?socket_list@@3USOCKET_STATE_LIST@@A */
extern ulong cb_arr[6];                    /* _cb_arr = ?callbacks@@3UCALLBACK_FUNC_LIST@@A */
extern void NET_MasterShutdown(void);      /* _NET_MasterShutdown = $FA$_t_40ae00 */
extern void socket_close_all(void);
extern void winsock_cleanup(void);
extern void __stdcall MMFreeAllId(ulong);  /* _MMFreeAllId@4 */

void __stdcall NET_Shutdown(void)
{
    if (tcp_proto.x288)
        return;
    tcp_proto.x288 = 1;
    if (netws) {
        if (player_list.started)
            NET_MasterShutdown();
        else
            socket_close_all();
        winsock_cleanup();
        *(long *)((char *)&mpInfo + 0x15c) = 0;
    }
    memset(cb_arr, 0, 24);
    MMFreeAllId(0x10);
    tcp_proto.x288 = 0;
    socket_list.x418 = -1;
    socket_list.x41c = -1;
}