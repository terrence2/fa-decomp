/* ?convert_addr_ipx2usnf@@YAXPAUNET_ADDRESS@@PAUsockaddr_ipx@@@Z @ 0x95300 — v1 */
typedef struct { unsigned long a; unsigned short b; } w28b_node6;

void w28b_ipx2u_ix(void *u, void *s)
{
    *(unsigned short *)u = 2;
    *(w28b_node6 *)((char *)u + 8) = *(w28b_node6 *)((char *)s + 6);
    *(long *)((char *)u + 4) = *(long *)((char *)s + 2);
    {
        unsigned short v = *(unsigned short *)((char *)s + 0xc);
        *(unsigned short *)((char *)u + 2) = (unsigned short)((v << 8) | (v >> 8));
    }
}
