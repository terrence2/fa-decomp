/* 0x64c90 v3: it's a POP (dec), not inc; rest of v2 was already exact */
extern void __fastcall w38b_err4(int a);
extern volatile short _w38b_st;
extern int _w38b_stt[1];

int w38b_64c90(void)
{
    if (_w38b_st <= 0) {
        w38b_err4(4);
    }
    _w38b_st--;
    return _w38b_stt[_w38b_st];
}