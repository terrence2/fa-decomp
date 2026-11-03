// _CTDo_btoh @ rva 0x656b0 = 415408, 80 B.
//   FA: mov al,[svc+0xec]; test al,al; jne ret; cmp word [ct+0x1f],0x3e90;
//   jge body; cmp word [ct+0x1f],0xc170; jg ret; body: 66 a1 [ct+0x21];
//   66 c7 05 [ct+0x21],0; 66 29 05 [ct+0x1d] (sub mem,ax); 66 8b 0d [ct+0x1d];
//   66 89 0d [ct+0x23]; ret.  Body runs when |v| >= 0x3e90 signed.
extern unsigned char _btohGate;   /* map __btohGate=_serviceTicks+0xec */
extern short _btohTF;             /* map __btohTF=_curThing+0x1f */
extern short _btohTT;             /* map __btohTT=_curThing+0x21 */
extern short _btohTL;             /* map __btohTL=_curThing+0x1d */
extern short _btohTD;             /* map __btohTD=_curThing+0x23 */

void CTDo_btoh(void)
{
    short v;
    if (_btohGate != 0)
        return;
    if (_btohTF < 0x3e90 && _btohTF > -16016)
        return;
    v = _btohTT;
    _btohTT = 0;
    _btohTL -= v;
    _btohTD = _btohTL;
}