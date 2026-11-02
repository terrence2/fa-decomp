/* ?convert_addr_ipx2usnf@@YAXPAUNET_ADDRESS@@PAUsockaddr_ipx@@@Z @ 0x95300
   — v3: fam store first (u loaded before s); bare decls; sd init before ud */
void w28b_ipx2u_f3(void *u, void *s)
{
    unsigned long *ud, *sd;
    unsigned short v;
    *(unsigned short *)u = 2;
    sd = (unsigned long *)((char *)s + 6);
    ud = (unsigned long *)((char *)u + 8);
    *ud = *sd;
    *(unsigned short *)((char *)ud + 4) = *(unsigned short *)((char *)sd + 4);
    *(unsigned long *)((char *)u + 4) = *(unsigned long *)((char *)s + 2);
    v = *(unsigned short *)((char *)s + 0xc);
    *(unsigned short *)((char *)u + 2) = (unsigned short)((v << 8) | (v >> 8));
}