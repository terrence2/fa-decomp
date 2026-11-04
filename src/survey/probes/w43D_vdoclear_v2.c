/* 0xabb80 ?VDOClearToBlack@@YAXXZ 0x80 — v2: stride-3k palette reads
 * (b1/b2 = byte-in-short-slot: mov dl + and 0xffff00ff, w43F idiom),
 * best = movsx'd k, G_Rect(0,0,gma,gmb), G_SetColor/G_Flush fastcall.
 */
extern short w43D_gma;   /* _grMode+0xa */
extern short w43D_gmb;   /* _grMode+0xc */
extern unsigned char w43D_pal2[];  /* _curPalette+2 */
extern unsigned char w43D_pal1[];  /* _curPalette+1 */
extern unsigned char w43D_pal0[];  /* _curPalette+0 */
extern long __fastcall w43D_gc(long best);
extern void __stdcall w43D_gr(long a1, long a2, long a3, long a4);
extern long __fastcall w43D_gf(long z);

void w43D_vdoclear(void)
{
    short minv;
    long best;
    short k;
    long k2, k3;
    short b1, b2, acc;
    minv = 190;
    best = -1L;
    k = 1;
    while (k < 0x100) {
        k2 = (long)k;
        acc = w43D_pal2[3*k2];
        b2 = w43D_pal1[3*k2];
        k3 = 3*k2;
        acc = (short)(acc + b2);
        b2 = w43D_pal0[k3];
        acc = (short)(acc + b2);
        if (acc < minv) {
            minv = acc;
            best = k2;
        }
        k++;
    }
    w43D_gc(best);
    w43D_gr(0, 0, (long)w43D_gma, (long)w43D_gmb);
    w43D_gf(0);
}
