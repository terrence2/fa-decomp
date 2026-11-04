/* ?socket_check_duplicates@@YADPAUsocket_state@@@Z @ 0xa3560 (154 B code + pads).
 * Duplicates scan over socket_list entries (stride 0x32):
 *   n = *(long *)socket_list; if (n <= 0) return 1;
 *   i = 0; eb = socket_list + 0x43c (entries/flag band, baked imm bb dc965600
 *   WITH FA reloc - DIR32 site on socket_list+0x43c);
 *   do {
 *     if (*(unsigned char *)eb) {
 *       ent = eb - 0x18 (lea edi,[ebx-0x18]);
 *       if (ent != me && net_addr_equal(ent+0x24, me+0x24)) goto dup;
 *     } else ent stays dead;
 *     eb += 0x32; i++;
 *   } while (*(long *)socket_list > i);   [39 2d cmp moffs,ebp; jg; count RE-READ]
 *   return 1;
 *  dup:
 *   if (*(long *)ent == -1) { socket_close(ent->sock); return 1; }  [83 3f ff; 8b 47 0c]
 *   pkt_sock_send_error(5, ent->sock);     [push eax(sockid) then 5 => (5, sockid); add esp,8]
 *   pkt_sock_send_error(5, me->sock);      [8b 46 0c; push eax; push 5]
 *   socket_flush_close(ent->sock);
 *   socket_flush_close(me->sock);
 *   return 0;
 * FA regs: ebp=count, ebx=eb (bb imm base), esi=me, edi=ent.
 * socket_state fields used: sock = +0xc, addr = +0x24; entry active byte at
 * +0x18 (flag band socket_list+0x43c = first entry's +0x18).
 */
extern char socket_list[];
extern char net_addr_equal(void *a, void *b);
extern void socket_close(long sock);
extern void pkt_sock_send_error(long code, long sock);
extern void socket_flush_close(long sock);

char socket_check_duplicates(char *me)
{
    long n, i;
    char *eb, *ent;

    n = *(long *)socket_list;
    i = 0;
    if (n <= i)
        return 1;
    eb = socket_list + 0x43c;
    do {
        ent = 0;
        if (*(unsigned char *)eb) {
            ent = eb - 0x18;
            if (ent != me && net_addr_equal(ent + 0x24, (char *)me + 0x24))
                goto dup;
        }
        eb += 0x32;
        i++;
    } while (*(long *)socket_list > i);
    return 1;
dup:
    if (*(long *)ent == -1) {
        socket_close(*(long *)(ent + 0xc));
        return 1;
    }
    pkt_sock_send_error(5, *(long *)(ent + 0xc));
    pkt_sock_send_error(5, *(long *)((char *)me + 0xc));
    socket_flush_close(*(long *)(ent + 0xc));
    socket_flush_close(*(long *)((char *)me + 0xc));
    return 0;
}