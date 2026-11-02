/* ?convert_addr_usnf2ipx@@YAXPAUsockaddr_ipx@@PAUNET_ADDRESS@@@Z @ 0x95340
   — v4: v2 shape with decls swapped (ud first: SRC local; FA leas ud-then-sd) */
void w28b_u2ipx_f4(void *s, void *u)
{
    unsigned long *ud = (unsigned long *)((char *)u + 8);
    unsigned long *sd = (unsigned long *)((char *)s + 6);
    *sd = *ud;
    *(unsigned short *)((char *)sd + 4) = *(unsigned short *)((char *)ud + 4);
    *(unsigned long *)((char *)s + 2) = *(unsigned long *)((char *)u + 4);
    {
        unsigned short v = *(unsigned short *)((char *)u + 2);
        *(unsigned short *)s = 6;
        *(unsigned short *)((char *)s + 0xc) = (unsigned short)((v << 8) | (v >> 8));
    }
}