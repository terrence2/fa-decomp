/* w40D_ae200: unnamed 64-B chunk @ 0x4ae200 (rva 0xae200), cdecl 2 args
 * push ebx/esi; ebx=arg2; push edi; edi=arg1; esi=edi+4
 * pkt_set_header(ebx, esi, 5); mov eax,[edi]; add word [edi+6],ax;
 * pkt_send(esi, ebx); test al; je L; mov dword [edi],0
 * maps: FROM = C++-mangled ?pkt_set_header@@YAXHPAUNET_PKT@@H@Z
 *       and ?pkt_send@@YADPAUNET_PKT@@H@Z
 */
struct NET_PKT;

void pkt_set_header(int, struct NET_PKT *, int);
char pkt_send(struct NET_PKT *, int);

void w40d_pktput(char *pkt, int x)
{
    pkt_set_header(x, (struct NET_PKT *)(pkt + 4), 5);
    *(unsigned short *)(pkt + 6) = *(unsigned short *)(pkt + 6)
        + *(unsigned int *)pkt;
    if (pkt_send((struct NET_PKT *)(pkt + 4), x))
        *(int *)pkt = 0;
}
/* end w40D */