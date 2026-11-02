/* ?MPPlayerChoseFort@@YIXE@Z @ 0x6ffa0 (64B) — v1: plain C, stores before call */
extern unsigned long w28b_numComp;                       /* -> _numComputers */
extern void __fastcall w28b_flush(unsigned char n);      /* -> ?MPFlushAll@@YIXD@Z */
extern void __stdcall w28b_send(long a, char *b, long c, long d);   /* -> $FA$_t_46b260 */

void __fastcall w28b_mpf_f(unsigned char side)
{
    char buf[4];
    if (w28b_numComp != 1) {
        buf[2] = ';';
        buf[3] = side;
        w28b_send(-1, &buf[2], 2, 1);
        w28b_flush(1);
    }
}
