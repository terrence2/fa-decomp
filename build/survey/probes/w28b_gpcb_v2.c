/* @G_PushClipBox@0 @ 0x95740 — v2: f[0] via scaled SIB then ushort* elem store */
typedef struct { unsigned short f[4]; } w28b_boxE;
extern unsigned long w28b_surfCnt;    /* -> _globalSecondarySurface */
extern unsigned long w28b_clipL;      /* -> _clipLeft */
extern unsigned long w28b_clipT;      /* -> _clipTop */
extern unsigned long w28b_clipW;      /* -> _clipWidth */
extern unsigned long w28b_clipH;      /* -> _clipHeight */
extern w28b_boxE w28b_boxT[];         /* -> _tempYLR+0x4b78 */

void __fastcall w28b_gpcb_f(void)
{
    unsigned long n = ++w28b_surfCnt;
    unsigned short *pp;
    w28b_boxT[n].f[0] = (unsigned short)w28b_clipL;
    pp = &w28b_boxT[n].f[0];
    pp[1] = (unsigned short)w28b_clipT;
    pp[2] = (unsigned short)w28b_clipW;
    pp[3] = (unsigned short)w28b_clipH;
}
