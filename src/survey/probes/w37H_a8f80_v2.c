/* ?tcpbuildaddress@@YADPAUNET_PROTOCOL@@PAUCN_INFO@@PAUNET_ADDRESS@@@Z
 * @ rva 0xa8f80 (96 B) -- v2.
 * v1 divergences fixed: (1) all c->tcp offsets are cast reads (f76 sits at
 * unaligned +0xdc6; the port is a 16-bit member read at +0xdb8, not a dword
 * read); (2) the 12-byte copy into tcp_settings is spelled as a 3-dword
 * struct assign so CL uses edi=base + [edi]/[edi+4]/[edi+8] pairs;
 * (3) no extra locals (v1 pushed ebp). */
typedef struct { unsigned long a0, a4, a8; } W37H_TP3;

typedef struct {
    unsigned short w0;
    unsigned short w2;
    unsigned long d4;
    unsigned long d8;
} W37H_ADDR;

extern struct W37H_TCP { unsigned char a[0x80]; } tcp_settings;  /* ?tcp_settings@@3UCN_INFO_TCP@@A */

char tcpbuildaddress(char* np, char* c, W37H_ADDR* d)
{
    unsigned short w;
    d->w0 = 1;
    d->d4 = *(unsigned long*)((char*)c + 0xdc6);
    *(W37H_TP3*)&tcp_settings = *(W37H_TP3*)((char*)c + 0xdb0);
    w = *(unsigned short*)((char*)c + 0xdb8);
    if (w == 0)
        d->w2 = 0x6ff;
    else
        d->w2 = w;
    return 1;
}