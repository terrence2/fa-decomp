// 0xad7c0 ?NET_MakeAutoConnectAddress@@YADPAUCN_INFO@@PAUNET_ADDRESS@@@Z (48 B)
// — v2 (|| merged single return-0 at the tail)
typedef char (__cdecl *PF27m)(char *proto, char *ci, char *addr);
extern char *proto_ptr27;

char __cdecl NetMakeAutoConn27(char *ci, char *addr)
{
    if (*(char *)((char *)ci + 0xdbc) == 0 || *(char *)((char *)ci + 0xdbd) == 0)
        return 0;
    return (*(PF27m *)((char *)proto_ptr27 + 0x6a))(proto_ptr27, ci, addr);
}
