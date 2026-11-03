/* chunk ?convert_addr_usnf2tcp@@YAXPAUsockaddr_in@@PAUNET_ADDRESS@@@Z
 * @ rva 0xa8ea0 (dec 691872, 80 B) — void __cdecl: dst = arg1 (sockaddr_in),
 * src = arg2 (NET_ADDRESS); same field layout: fam@0 word, port@2 word,
 * addr@4 dword. FA: addr byte-swap via ((a&0xff00)|(a<<16))<<8 |
 * ((a&0xff0000)|(a>>16))>>8, then port read + fam=2 interleaved, port
 * byte-swap via byte moves (dh=dl ; dl=ch).
 */
typedef struct { unsigned short fam; unsigned short port; unsigned long addr; }
    W31G_ADDR;

void __cdecl w31g_usnf2tcp(W31G_ADDR *dst, W31G_ADDR *src)
{
    unsigned long a;
    unsigned short p;
    a = src->addr;
    dst->addr = ((a & 0xff00) | (a << 16)) << 8
              | (((a & 0xff0000) | (a >> 16)) >> 8);
    p = src->port;
    dst->fam = 2;
    dst->port = ((p & 0xff) << 8) | (p >> 8);
}
