/* w42B 0x5ccc50 — twin of pktnew v2 with header type 0x15. */
extern void pkt_set_header(int flag, char *p, int msg);
extern char *strcpy(char *d, const char *s);

void pkt_build_lost_player(char *pkt, int id, char *pad, char *addr)
{
    char *d;
    pkt_set_header(-1, pkt, 0x15);
    *(unsigned short *)(pkt + 4) = (unsigned short)id;
    d = pkt + 6;
    *(unsigned long *)d = *(unsigned long *)addr;
    *(unsigned long *)(d + 4) = *(unsigned long *)(addr + 4);
    *(unsigned long *)(d + 8) = *(unsigned long *)(addr + 8);
    *(unsigned short *)(d + 0xc) = *(unsigned short *)(addr + 0xc);
    strcpy(pkt + 0x14, pad);
}