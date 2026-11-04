/* w46B_gvisible_v1 - _G_Visible, FA rva 0x96b80 (617344), 160 B, tail 2x 8da42400000000 (14 B census pad)
 * cdecl, sub esp,0x10 BEFORE 4 reg pushes (ebx,esi,edi,ebp); ebp = loop counter.
 * locals esp: x1@+0x1c, y1@+0x18, x2@+0x14, y2@+0x10 (decl order stored high->low).
 * pts = array of 20-B stride pairs: x=pts[5*i] sar 16, y=pts[5*i+1] sar 16.
 * next index j = (i - n == -1) ? 0 : i + 1 (wrap). Call G_ClipLine(&x1,&y1,&x2,&y2);
 * if TRUE return 1. Else loop; exhausted -> 0.
 * rel site: 0x6a call _G_ClipLine @0x495f10 (public).
 */
extern char G_ClipLine(long *x1, long *y1, long *x2, long *y2);

char G_Visible(long n, long *pts)
{
    long x1, y1, x2, y2;
    long i;
    for (i = 0; i < n; i++)
    {
        long j;
        x1 = pts[5 * i] >> 16;
        y1 = pts[5 * i + 1] >> 16;
        j = (i - n == -1) ? 0 : i + 1;
        x2 = pts[5 * j] >> 16;
        y2 = pts[5 * j + 1] >> 16;
        if (G_ClipLine(&x1, &y1, &x2, &y2))
            return 1;
    }
    return 0;
}