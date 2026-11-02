/* @G_PushClipBox@0 @ 0x95740 — v1 */
typedef struct { unsigned short f[4]; } w28b_boxE;
extern unsigned long w28b_surfCnt;    /* -> _globalSecondarySurface+0x4 */
extern unsigned long w28b_clipL;      /* -> _clipLeft */
extern unsigned long w28b_clipT;      /* -> _clipTop */
extern unsigned long w28b_clipW;      /* -> _clipWidth */
extern unsigned long w28b_clipH;      /* -> _clipHeight */
extern w28b_boxE w28b_boxT[];         /* -> _tempYLR+0x4e18 */

void __fastcall w28b_gpcb_f(void)
{
    unsigned long n = ++w28b_surfCnt;
    w28b_boxT[n].f[0] = (unsigned short)w28b_clipL;
    w28b_boxT[n].f[1] = (unsigned short)w28b_clipT;
    w28b_boxT[n].f[2] = (unsigned short)w28b_clipW;
    w28b_boxT[n].f[3] = (unsigned short)w28b_clipH;
}
