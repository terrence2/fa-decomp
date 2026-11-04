/* w35B: _G_Vline@12 @ rva 0x95c30 (96 B)
 * FA: push ebx; eax=clipLeft (a1); push esi; push edi; esi=[esp+0x10] (y);
 * if clipLeft>y skip; eax=clipRight; if clipRight<y skip;
 * ebx=[esp+0x18] (x); edi=[esp+0x14] (y2);
 * if x<y2 PrintShapeName();
 * eax=clipTop; if clipTop>edi edi=eax (min);
 * eax=clipBottom; if clipBottom<ebx ebx=eax (min);
 * if ebx<edi skip; push ebx; push edi; push esi; call _G_UVline@12;
 * pop edi; pop esi; pop ebx; ret 0xc.
 */
extern void __stdcall PrintShapeName(void);
extern void __stdcall G_UVline(long a, long b, long c);
extern long clipLeft, clipRight, clipTop, clipBottom;

void __stdcall G_Vline(long y, long y2, long x)
{
    if (clipLeft <= y && clipRight >= y) {
        long t = y2, b = x;
        if (x < y2)
            PrintShapeName();
        if (clipTop < t)
            t = clipTop;
        if (clipBottom < b)
            b = clipBottom;
        if (b >= t)
            G_UVline(y, t, b);
    }
}