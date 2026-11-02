// _PushCurObj@4 v4 — load index FIRST (a1 -> eax), then id via 66 8b 0d
// (eax taken -> generic form, cx live for the test); inc via a1/40/a3.
extern unsigned short w27a_curIdI;     /* _curId */
extern unsigned int w27a_ccp1c;        /* ?correctChainPlacement@@3DA+0x1c */
extern unsigned short w27a_chainArr[]; /* ?correctChainPlacement@@3DA+0x8 */
extern void __fastcall PutCurObj_f(void);             /* @PutCurObj@0 */
extern void __fastcall GetCurObj_f(unsigned short w); /* @GetCurObj@4 */
void __stdcall w27a_pco_q(unsigned short w)
{
    unsigned int ix;
    unsigned short id;
    ix = w27a_ccp1c;
    id = w27a_curIdI;
    w27a_chainArr[ix] = id;
    if (id != 0)
        PutCurObj_f();
    w27a_ccp1c = w27a_ccp1c + 1;
    GetCurObj_f(w);
}
