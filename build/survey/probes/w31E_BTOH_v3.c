// _CTDo_btoh @ rva 0x656b0 = 415408, 80 B. v3: v as unsigned short to push
// the 66 a1 moffs load of _btohTT into AX (FA: 66 a1; then sub word mem,ax).
extern unsigned char _btohGate;
extern short _btohTF1, _btohTF2;
extern unsigned short _btohTT;
extern short _btohTL, _btohTL2, _btohTD;

void CTDo_btoh(void)
{
    unsigned short v;
    if (_btohGate != 0)
        return;
    if (_btohTF1 < 0x3e90 && _btohTF2 > -16016)
        return;
    v = _btohTT;
    _btohTT = 0;
    _btohTL -= v;
    _btohTD = _btohTL2;
}