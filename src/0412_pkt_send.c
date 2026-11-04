/* w46B_pktsend_v1 - ?pkt_send@@YADPAUNET_PKT@@H@Z, FA rva 0x5cfa0 (380832), 160 B, tail 8d642400 (4 B census pad)
 *
 * FA anatomy (cdecl, FPO esp-frame, cbRegs=2 push esi,edi, locals=0, params=2):
 *   00 mov eax,[esp+8] (n); push esi/edi; mov edi,[esp+c] (pkt)
 *   0a mov esi,[eax*4+player_list+0x66]                       (list entry)
 *   10 mov ecx,[esi+0x2c92]; test; jle slow
 *   1a mov ax,[pkt+2]; push eax/edi/esi; call $FA$_t_45d060 (SendToPlayer(pl,pkt,len))
 *      add esp,0xc; pop edi/esi; ret  (eax passthrough)
 *   slow: push 0; xor eax; mov ax,[pkt+2]; mov ecx,[esi] (sock);
 *      push eax/edi/ecx; call [ws+0x42]  (send(sock,pkt,len,0) stdcall)
 *   40 mov cx,[pkt+2]; mov edx,ecx; and edx,0xffff; cmp edx,eax; je ok
 *   50 cmp eax,-1; jne rem  (sent != -1)
 *      call [ws+0xe] (WSAGetLastError); cmp 0x2733 (WSAEWOULDBLOCK);
 *      jne doa: re-send via SendToPlayer(pl,pkt,[pkt+2]) passthrough ret
 *      else socket_set_doa([esi]); xor al,al; ret (return 0)
 *   rem: sub cx,ax (remaining); lea eax,[edi+eax] (pkt+sent);
 *      push ecx/eax/esi; call SendToPlayer; ret passthrough
 *   ok: mov al,1; ret (return 1)
 */
typedef unsigned long (__stdcall *PSEND)(unsigned long, const void *, int, int);
typedef unsigned long (__stdcall *PWSAE)(void);
extern unsigned char plp_[0x10000];     /* ?player_list@@3UNET_PLAYER_LIST@@A */
extern PSEND pSend;                     /* ?ws@@3U_winsock_funcs@@A + 0x42 */
extern PWSAE pWsaGetLastError;          /* ?ws@@3U_winsock_funcs@@A + 0xe */
extern long SendToPlayer(void *pl, void *pkt, unsigned long len); /* $FA$_t_45d060 */
extern void socket_set_doa(unsigned long sock);   /* ?socket_set_doa@@YAXI@Z */

char pkt_send(void *pkt, int n)
{
    void *pl;
    unsigned long sent;
    unsigned short w;
    pl = *(void **)(plp_ + 0x66 + 4 * n);
    if (*(long *)((char *)pl + 0x2c92) > 0)
        return SendToPlayer(pl, pkt, *(unsigned short *)((char *)pkt + 2));
    w = *(unsigned short *)((char *)pkt + 2);
    sent = pSend(*(unsigned long *)pl, pkt, w, 0);
    w = *(unsigned short *)((char *)pkt + 2);
    if ((unsigned long)(unsigned short)w == sent)
        return 1;
    if (sent != (unsigned long)-1)
        return SendToPlayer(pl, (char *)pkt + sent, w - (unsigned short)sent);
    if (pWsaGetLastError() == 0x2733)
        return SendToPlayer(pl, pkt, *(unsigned short *)((char *)pkt + 2));
    socket_set_doa(*(unsigned long *)pl);
    return 0;
}