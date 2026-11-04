/* 0x23ce0: nationSides fastcall selector -> specials/worldCenter word reads */
extern void *__fastcall w38b_23ad0(int a, int b);
extern int _w38b_ns64;
extern int _w38b_ns6c;
extern int _w38b_sp;
extern int _w38b_wc;

void w38b_23ce0(void)
{
    void *r = w38b_23ad0(_w38b_ns64, _w38b_ns6c);
    if (r != 0) {
        _w38b_sp = *(short *)((char *)r + 4);
        _w38b_wc = *(short *)((char *)r + 6);
    }
}