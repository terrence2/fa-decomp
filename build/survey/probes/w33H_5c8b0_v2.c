/* v2: dst local declared BEFORE the call (FA: lea edi,[esi+4] hoisted
 * pre-call); strlen scans the COPIED buffer dst (edi), not str; the
 * str load then lands in eax for the src arg. */
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
    p->len += strlen(dst) + 1;
}
