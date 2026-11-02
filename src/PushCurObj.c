// _PushCurObj@4 @ rva 0x61ba0 (64 B) — mov cx,_curId; mov eax,_ccp1c (a1);
// store word _chainArr[n] (66 89 0c 45, sib x2, base = _ccp+0x8); test cx;
// je; call @PutCurObj@0; mov eax,_ccp1c (reload); inc eax; mov ecx,[esp+4];
// mov _ccp1c,eax (a3); call @GetCurObj@4; ret 4.
extern unsigned short w27a_curIdI;     /* _curId */
extern unsigned int w27a_ccp1c;        /* ?correctChainPlacement@@3DA+0x1c */
extern unsigned short w27a_chainArr[]; /* ?correctChainPlacement@@3DA+0x8 */
extern void __fastcall PutCurObj_f(void);            /* @PutCurObj@0 */
extern void __fastcall GetCurObj_f(unsigned short w);/* @GetCurObj@4 */
void __stdcall w27a_pco_q(unsigned short w)
{
    unsigned short id;
    id = w27a_curIdI;
    w27a_chainArr[w27a_ccp1c] = id;
    if (id != 0)
        PutCurObj_f();
    w27a_ccp1c = w27a_ccp1c + 1;
    GetCurObj_f(w);
}