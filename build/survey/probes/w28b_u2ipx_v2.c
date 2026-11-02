/* ?convert_addr_usnf2ipx@@YAXPAUsockaddr_ipx@@PAUNET_ADDRESS@@@Z @ 0x95340
   — v2: shifted pointer locals; fam store between swap moves */
void w28b_u2ipx_f2(void *s, void *u)
{
    unsigned long *sd = (unsigned long *)((char *)s + 6);
    unsigned long *ud = (unsigned long *)((char *)u + 8);
    *sd = *ud;
    *(unsigned short *)((char *)sd + 4) = *(unsigned short *)((char *)ud + 4);
    *(unsigned long *)((char *)s + 2) = *(unsigned long *)((char *)u + 4);
    {
        unsigned short v = *(unsigned short *)((char *)u + 2);
        *(unsigned short *)s = 6;
        *(unsigned short *)((char *)s + 0xc) = (unsigned short)((v << 8) | (v >> 8));
    }
}
