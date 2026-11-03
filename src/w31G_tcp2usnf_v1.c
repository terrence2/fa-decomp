/* chunk ?convert_addr_tcp2usnf@@YAXPAUNET_ADDRESS@@PAUsockaddr_in@@@Z
 * @ rva 0xa8ef0 (dec 691952, 80 B) — sibling twin: dst = arg1
 * (NET_ADDRESS, fam = 1 stored first), src = arg2 (sockaddr_in).
 */
typedef struct { unsigned short fam; unsigned short port; unsigned long addr; }
    W31G_ADDR;

void __cdecl w31g_tcp2usnf(W31G_ADDR *dst, W31G_ADDR *src)
{
    unsigned long a;
    unsigned short p;
    dst->fam = 1;
    a = src->addr;
    dst->addr = ((a & 0xff00) | (a << 16)) << 8
              | (((a & 0xff0000) | (a >> 16)) >> 8);
    p = src->port;
    dst->port = ((p & 0xff) << 8) | (p >> 8);
}
