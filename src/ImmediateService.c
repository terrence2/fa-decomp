// _ImmediateService@0 @ rva 0x61870 — RemoveFromChains(), chainFlag = 0
//   (the _curThing+0x68 word), then fastcall tail into $FA$_t_461890 with
//   &chainStart (probe d102 exact).
extern unsigned int chainStart;
extern unsigned short chainFlag;
extern void __stdcall RemoveFromChains(void);
extern void __fastcall t61890(char *p);

void ImmediateService_q(void)
{
    RemoveFromChains();
    chainFlag = 0;
    t61890((char *)&chainStart);
}
