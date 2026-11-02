// _PushCurObj@4 — single statement: LHS index loads via a1, RHS id via
// 66 8b 0d into cx, sib store 66 89 0c 45; test cx (CSE across the if).
extern unsigned short w27a_curIdI;     /* _curId */
extern unsigned int w27a_ccp1c;        /* ?correctChainPlacement@@3DA+0x1c */
extern unsigned short w27a_chainArr[]; /* ?correctChainPlacement@@3DA+0x8 */
extern void __fastcall PutCurObj_f(void);             /* @PutCurObj@0 */
extern void __fastcall GetCurObj_f(unsigned short w); /* @GetCurObj@4 */
void __stdcall w27a_pco_q(unsigned short w)
{
    w27a_chainArr[w27a_ccp1c] = w27a_curIdI;
    if (w27a_curIdI != 0)
        PutCurObj_f();
    w27a_ccp1c = w27a_ccp1c + 1;
    GetCurObj_f(w);
}
