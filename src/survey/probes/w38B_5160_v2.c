/* 0x5160 v2: value of the compare feeds the store (keeps eax), store cs first */
extern int _thisComputerX;
extern long _w38b_mns;
extern short _w38b_cs;

void w38b_5160(void)
{
    if (_thisComputerX > 0 && _w38b_mns != -1) {
        _w38b_cs = (short)_w38b_mns;
        _w38b_mns = -1;
    }
}