// @PutCurObj@0 @ rva 0x61b40 (64 B) — copy the current thing into the chain
// slot. FA: push esi; edx = word[chainStart+0x4] (33 d2/66 8b 15 widen);
// push edi; esi=&_curThing (be imm w/ reloc); eax = word[_curId] (33 c0/66
// a1 widen); ecx=edx>>2; nop; edi=objPtrs[id] (8b 3c 85, sib-85 scale4);
// rep movsd; ecx=edx&3; rep movsb; word[_curId]=0 (66 c7 05); pop edi/esi;
// ret. EXACT as plain C (wave-23 probe v2): inline memcpy(d, curThing, n)
// with the two ushort widen locals (id in eax via objPtrs subscripting,
// size in edx via the memcpy count) reproduces the xor+mov16 widenings,
// the sib-85 dest load, both rep blocks and the 66 c7 05 tail store; v1
// (subscripted d local + id-first order) differed only at FA's lone nop.
// Maps: _objSizeW=?chainStart@@3GA+0x4, _curThingB=_curThing, _curIdW=_curId,
// _objPtrsA=_objPtrs.
#include <string.h>
extern unsigned short objSizeW;   /* ?chainStart@@3GA+0x4 */
extern unsigned short curIdW;     /* _curId */
extern char curThingB[];          /* _curThing */
extern char objPtrsA[];           /* _objPtrs */

void __fastcall PutCurObj_q(void)
{
    unsigned long n;
    unsigned long id;
    memcpy(((char **)objPtrsA)[curIdW], curThingB, objSizeW);
    curIdW = 0;
}