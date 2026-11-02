// ?pkt_sock_send@@YADPAUNET_PKT@@I@Z @ rva 0x5cf70 — C v1
typedef void (__stdcall *WSSEND)(unsigned long, void *, unsigned long, unsigned long);
extern WSSEND wsendX;            /* ?ws@@3U_winsock_funcs@@A+0x42 */

char __cdecl pkt_sock_sendq(void *pkt, unsigned long w)
{
    unsigned short l;
    unsigned long sent;

    l = *(unsigned short *)((char *)pkt + 2);
    sent = wsendX(w, pkt, l, 0);
    return (unsigned long)*(unsigned short *)((char *)pkt + 2) == (unsigned long)(unsigned short)sent;
}
