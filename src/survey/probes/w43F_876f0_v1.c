/* w43F 0x876f0 _DialogSetString@12 (144 B, stdcall 3 args ret 0xc): arg1 ->
 * @DialogGetPtr@4 (fastcall); switch (*(ushort*)o & 0x7fff) with the 81 e1
 * and long form, cmp 9 / ja unsigned, selector byte table at chunk+0x78 and
 * 5-dword jump table at chunk+0x64 (case 0 -> [o+0x1a]+p3-guard[o+0x1e],
 * case 2 -> [o+0x14], case 4 -> [o+0x20], case 9 -> [o+0xa] + p3-guard
 * [o+0xe], default 1/3/5/6/7/8 -> shared ret).
 */
extern void *__fastcall w43F_DGP(long a);

void __stdcall w43F_DSS(long dlg, long p2, long p3)
{
    unsigned long v;
    void *o;
    o = w43F_DGP(dlg);
    v = (unsigned long)*(unsigned short *)o & 0x7fffu;
    switch (v) {
    case 0:
        *(long *)((char *)o + 0x1a) = p2;
        if (p3 != (long)0) *(long *)((char *)o + 0x1e) = p3;
        break;
    case 2:
        *(long *)((char *)o + 0x14) = p2;
        break;
    case 4:
        *(long *)((char *)o + 0x20) = p2;
        break;
    case 9:
        *(long *)((char *)o + 0xa) = p2;
        if (p3 != (long)0) *(long *)((char *)o + 0xe) = p3;
        break;
    }
}