// ?pkt_sock_send@@YADPAUNET_PKT@@I@Z @ rva 0x5cf70 — C v2 (callee returns unsigned long)
typedef unsigned long (__stdcall *WSSEND)(unsigned long, void *, unsigned long, unsigned long);
extern WSSEND wsendX;            /* ?ws@@3U_winsock_funcs@@A+0x42 */

char __cdecl pkt_sock_sendq(void *pkt, unsigned long w)
{
    unsigned long sent;

    sent = wsendX(w, pkt, (unsigned long)*(unsigned short *)((char *)pkt + 2), 0);
    return (unsigned long)*(unsigned short *)((char *)pkt + 2) == sent;
}
