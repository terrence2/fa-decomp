/* ?convert_addr_usnf2ipx@@YAXPAUsockaddr_ipx@@PAUNET_ADDRESS@@@Z @ 0x95340
   — v3: copy1 fully inline (value load first), ud/sd locals from copy2 */
void w28b_u2ipx_f3(void *s, void *u)
{
    unsigned long *ud, *sd;
    unsigned short v;
    *(unsigned long *)((char *)s + 6) = *(unsigned long *)((char *)u + 8);
    ud = (unsigned long *)((char *)u + 8);
    sd = (unsigned long *)((char *)s + 6);
    *(unsigned short *)((char *)ud + 4) = *(unsigned short *)((char *)sd + 4);
    *(unsigned long *)((char *)s + 2) = *(unsigned long *)((char *)u + 4);
    v = *(unsigned short *)((char *)u + 2);
    *(unsigned short *)s = 6;
    *(unsigned short *)((char *)s + 0xc) = (unsigned short)((v << 8) | (v >> 8));
}