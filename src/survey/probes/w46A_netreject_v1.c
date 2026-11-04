/* rva 0xad70 (?NET_MasterRejectPlayer@@YAXPAUNET_ADDRESS@@PAD@Z 44400). Walks ?player_list@@3UNET_PLAYER_LIST@@A+0x66 slot table (offs 32/78/98) comparing net_addr_equal; on hit sends pkt_sock_send_error(3,...) + socket_flush_close and calls unnamed chunk $FA$_t_40b4a0 (rel32, link-stable). Transplant: 5 DIR32 newsites offs 23,32,65,78,98.. */
int w46a_netrej_stub(void) { return 0; }
