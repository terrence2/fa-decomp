/* _G_PrintOutline@24 @ 0x96a20 (144 B): 3x3 text outline then color print.
 * void __stdcall G_PrintOutline(int y1, int x1, int p3, int p4, int p5, int p6)
 *   G_SetColor(p6);                              [mov ecx,[esp+0x18](p6); call @4 FIRST]
 *   for (y = y1-1; y <= y1+1; y++)               [dec esi; ylimit=p1+1 local; cmp esi,yl; jg skip;
 *                                                 ...; inc esi; cmp esi,[yl]; jle back]
 *       for (x = x1-1; x <= x1+1; x++)           [x0 local p2-1; xhi local p2+1;
 *                                                 check xhi<x skip; loop inc ebp; cmp ebp,xhi; jle]
 *           G_Print(y, x, p3, p4);               [push ebx(p4); edx=ebp(x); push edi(p3);
 *                                                 ecx=esi(y); call @G_Print@16 fastcall]
 *   G_SetColor(p5);                              [mov ecx,[esp+0x30](p5); call]
 *   G_Print(y1, x1, p3, p4);                     [edx=[+0x24](p2); push ebx; ecx=[+0x24](p1);
 *                                                 push edi; call]
 * locals: 3 dwords (sub esp,0xc) = ylimit / x0 / xhi
 * G_Print(text?, ...) fastcall @16 = 4 dwords (ecx, edx, stack x2)
 */
extern void __fastcall G_SetColor(int c);
extern void __fastcall G_Print(int a1, int a2, int a3, int a4);

void __stdcall G_PrintOutline(int y1, int x1, int p3, int p4, int p5, int p6)
{
    int y;
    int x;

    G_SetColor(p6);
    for (y = y1 - 1; y <= y1 + 1; y++)
        for (x = x1 - 1; x <= x1 + 1; x++)
            G_Print(y, x, p3, p4);
    G_SetColor(p5);
    G_Print(y1, x1, p3, p4);
}