// _CTDo_btoh @ rva 0x656b0 = 415408, 80 B. v4: like v2 but the subtract is
// spelled as an explicit difference.
extern unsigned char _btohGate;
extern short _btohTF1, _btohTF2;
extern short _btohTT;
extern short _btohTL, _btohTL2, _btohTD;

void CTDo_btoh(void)
{
    short v;
    if (_btohGate != 0)
        return;
    if (_btohTF1 < 0x3e90 && _btohTF2 > -16016)
        return;
    v = _btohTT;
    _btohTT = 0;
    _btohTL = _btohTL - v;
    _btohTD = _btohTL2;
}