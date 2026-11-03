/* rva 0x5c8b0 (80 B) pkt_build_message(UNET_PKT* p, ushort msg, char* s):
 * pkt_set_header(-1, p, msg); strncpy(p->data, str, 0x200);
 * p->len += strlen(str) + 1  (word add at p+2; data at p+4).
 * FA inlines strlen as ecx=-1/xor eax/repnz scasb/not ecx. */
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
    pkt_set_header(-1, p, msg);
    strncpy(p->data, str, 0x200);
    p->len += strlen(str) + 1;
}
