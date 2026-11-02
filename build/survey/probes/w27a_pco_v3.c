// v3: local id + single arr statement (index-eval-first -> a1/66 8b 0d).
extern unsigned short w27a_curIdI;
extern unsigned int w27a_ccp1c;
extern unsigned short w27a_chainArr[];
extern void __fastcall PutCurObj_f(void);
extern void __fastcall GetCurObj_f(unsigned short w);
void __stdcall w27a_pco_q(unsigned short w)
{
    unsigned short id;
    id = w27a_curIdI;
    w27a_chainArr[w27a_ccp1c] = id;
    if (id != 0)
        PutCurObj_f();
    w27a_ccp1c++;
    GetCurObj_f(w);
}
