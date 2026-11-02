/* ?convert_addr_usnf2ipx@@YAXPAUsockaddr_ipx@@PAUNET_ADDRESS@@@Z @ 0x95340 — v1 */
typedef struct { unsigned long a; unsigned short b; } w28b_node6;

void w28b_u2ipx_ui(void *s, void *u)
{
    *(w28b_node6 *)((char *)s + 6) = *(w28b_node6 *)((char *)u + 8);
    *(long *)((char *)s + 2) = *(long *)((char *)u + 4);
    {
        unsigned short v = *(unsigned short *)((char *)u + 2);
        *(unsigned short *)((char *)s + 0xc) = (unsigned short)((v << 8) | (v >> 8));
    }
    *(unsigned short *)s = 6;
}
