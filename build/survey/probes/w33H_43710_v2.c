/* v2: msg43 declared stdcall (FA callee cleans 0x14).  FA blend bytes:
 * mov eax,a5; (pushes) mov al,[E+4]=byte a1; and eax,0xffff00ff — forced
 * by byte-write into the local copy of a5.  Post-call reads: [esp+0x10]=a3
 * word -> obj+4; [esp+0x14]=a4 pointer (copy/zero 6 B at obj+0x1c).
 * NULL path zero-stores words 0x20,0x1e,0x1c in FA order. */
extern int __stdcall w33h_msg43(int a, unsigned b, int c, int d, int e);

int __stdcall GRAPHICAddInvisible(int a1, int a2, int a3, int a4, int a5)
{
    unsigned b;
    int obj;
    b = a5;
    *(unsigned char *)&b = (unsigned char)a1;
    b &= 0xffff00ffu;
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
