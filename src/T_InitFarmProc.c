// _T_InitFarmProc @ rva 0xa54d0 (16 B) — mov ecx,_makeTargetList+0x1070 /
//   jmp $FA$t_4a4db0 — fastcall thunk: hand the target-list walker its
//   context pointer (a jmp tail call; fastcall callee pops its own arg).
extern unsigned char makeTargetList[];
extern void __fastcall farmProc_(int ctx);

void T_InitFarmProc(void)
{
    farmProc_((int)(makeTargetList + 0x1070));
}