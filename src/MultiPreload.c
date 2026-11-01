// _MultiPreload @ rva 0x87930 — shell-alloc wrap, four dialog-preload calls
extern void __stdcall pushSA(void);
extern void __stdcall popSA(void);
extern void __fastcall pf960(int a);
void MultiPreload_q(void)
{
    pushSA();
    pf960(1);
    pf960(0);
    pf960(3);
    pf960(4);
    popSA();
}
