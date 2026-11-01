// _GrafPrefPreload @ rva 0x878c0 — shell-alloc wrap around the graf-pref dialogs
extern void __stdcall pushSA(void);
extern void __stdcall popSA(void);
extern void __stdcall TopCenterDialogFn(void);
extern void __fastcall pf960(int a);
extern void __stdcall pf3e0(void);
extern void __stdcall pf440(void);
void GrafPrefPreload_q(void)
{
    pushSA();
    TopCenterDialogFn();
    pf960(1);
    pf960(0);
    pf3e0();
    pf440();
    popSA();
}
