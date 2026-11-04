/* 0x65450 v3: volatile table too, forces store-before-inc */
extern void __fastcall w38b_err5(int a);
extern volatile short _w38b_st2;
extern volatile int _w38b_stt2[1];

void __fastcall w38b_65450(int val)
{
    if (_w38b_st2 >= 0x14) {
        w38b_err5(5);
    }
    _w38b_stt2[_w38b_st2] = val;
    _w38b_st2++;
}