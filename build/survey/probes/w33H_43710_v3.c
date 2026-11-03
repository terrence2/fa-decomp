/* v3 = v3a: no address-taken local (v2's *(char*)&b spilled b to a stack
 * temp: 83ec04/mov[esp]); blend as single expression tree. */
extern int __stdcall w33h_msg43(int a, unsigned b, int c, int d, int e);

int __stdcall GRAPHICAddInvisible(int a1, int a2, int a3, int a4, int a5)
{
    unsigned b, obj;
    b = (a5 & 0xffff0000u) | (a1 & 0xffu);
    obj = w33h_msg43(0x2b, b, a2, a5, -1);
    if (!obj)
        return 0;
    *(unsigned short *)(obj + 4) = (unsigned short)a3;
    if (a4)
        *(unsigned *)(obj + 0x1c) = *(unsigned *)a4,
        *(unsigned short *)(obj + 0x20) = *(unsigned short *)(a4 + 4);
    else
        *(unsigned short *)(obj + 0x20) = 0,
        *(unsigned short *)(obj + 0x1e) = 0,
        *(unsigned short *)(obj + 0x1c) = 0;
    return obj;
}
