/* v4: no address-taken locals; blend = single a5-first tree (v1 shape put
 * a5's copy in esi = prolog push esi, so esi is live: FA's lea-esi dst and
 * the 5e pops all need esi enreg'd); stdcall msg43 (callee cleans 0x14);
 * dst-pointer local inside the a4 branch (FA's lea esi,[eax+0x1c]).
 * PROVENANCE WILL PATCH the prolog band: FA loads a5->eax/a2->ecx and
 * emits mov-al-then-and-0xffff00ff fused mask; CL picks different regs. */
extern int __stdcall w33h_msg43(int a, unsigned b, int c, int d, int e);

int __stdcall GRAPHICAddInvisible(int a1, int a2, int a3, int a4, int a5)
{
    unsigned b, obj;
    b = (a5 & 0xffff0000u) | (a1 & 0xffu);
    obj = w33h_msg43(0x2b, b, a2, a5, -1);
    if (!obj)
        return 0;
    *(unsigned short *)(obj + 4) = (unsigned short)a3;
    if (a4) {
        b = (unsigned)(obj + 0x1c);
        *(unsigned *)b = *(unsigned *)a4;
        *(unsigned short *)(b + 4) = *(unsigned short *)(a4 + 4);
    } else {
        *(unsigned short *)(obj + 0x20) = 0;
        *(unsigned short *)(obj + 0x1e) = 0;
        *(unsigned short *)(obj + 0x1c) = 0;
    }
    return obj;
}
