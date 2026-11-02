/* ?convert_addr_ipx2usnf@@YAXPAUNET_ADDRESS@@PAUsockaddr_ipx@@@Z @ 0x95300
   — v2: shifted pointer locals induce the lea+2-move copy */
void w28b_ipx2u_f2(void *u, void *s)
{
    unsigned long *sd = (unsigned long *)((char *)s + 6);
    unsigned long *ud = (unsigned long *)((char *)u + 8);
    *(unsigned short *)u = 2;
    *ud = *sd;
    *(unsigned short *)((char *)ud + 4) = *(unsigned short *)((char *)sd + 4);
    *(unsigned long *)((char *)u + 4) = *(unsigned long *)((char *)s + 2);
    {
        unsigned short v = *(unsigned short *)((char *)s + 0xc);
        *(unsigned short *)((char *)u + 2) = (unsigned short)((v << 8) | (v >> 8));
    }
}
