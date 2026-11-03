// _CTDo_btoh @ rva 0x656b0 = 415408, 80 B. v2: twin symbols mapped to the
// same interior addresses force FA's two memory compares (_btohTF1/_btohTF2
// both = _curThing+0x1f), and a separate _btohTL2 (= _curThing+0x1d) forces
// the final TD=TL reload instead of a register CSE.
extern unsigned char _btohGate;   /* _serviceTicks+0xec */
extern short _btohTF1;            /* _curThing+0x1f */
extern short _btohTF2;            /* _curThing+0x1f */
extern short _btohTT;             /* _curThing+0x21 */
extern short _btohTL;             /* _curThing+0x1d */
extern short _btohTL2;            /* _curThing+0x1d */
extern short _btohTD;             /* _curThing+0x23 */

void CTDo_btoh(void)
{
    short v;
    if (_btohGate != 0)
        return;
    if (_btohTF1 < 0x3e90 && _btohTF2 > -16016)
        return;
    v = _btohTT;
    _btohTT = 0;
    _btohTL -= v;
    _btohTD = _btohTL2;
}