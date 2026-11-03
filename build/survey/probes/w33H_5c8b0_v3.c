/* v3 = v2 + p->data[0x1ff] = 0 (FA's mov byte [esi+0x203],0 — REAL
 * instruction dis.py elided; caught in raw bytes). */
struct UNET_PKT {
    char pad[2];
    unsigned short len;
    char data[0x200];
};
extern void pkt_set_header(int flag, struct UNET_PKT *p, int msg);
extern char *strncpy(char *d, const char *s, unsigned n);
extern unsigned strlen(const char *s);

void pkt_build_message(struct UNET_PKT *p, unsigned short msg, char *str)
{
    char *dst;
    dst = p->data;
    pkt_set_header(-1, p, msg);
    strncpy(dst, str, 0x200);
    p->data[0x1ff] = 0;
    p->len += strlen(dst) + 1;
}
