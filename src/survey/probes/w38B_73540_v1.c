/* 0x73540: Kill + conditional RemoveCurObj + GRAPHICAddCrater(3-arg) */
extern void w38b_kil(void);
extern void w38b_rmo(void);
extern void __fastcall w38b_gc(int a, void *b, int c);
extern int _thisComputer;
extern int _w38b_think;
extern unsigned char _w38b_cb;
extern int _w38b_ttype;

void w38b_73540(void)
{
    w38b_kil();
    if (_w38b_ttype == 0) {
        w38b_rmo();
    }
    w38b_gc(_thisComputer, &_w38b_think, (int)_w38b_cb);
}