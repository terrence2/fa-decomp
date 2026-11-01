// ?T_VietRicePaddy3Proc@@YAXJ@Z @ rva 0xa57f0 (16 B) — cdecl stack-param
// thunk: mov eax,[esp+4]/push eax/call ?T_VietRicePaddy1Proc@@YAXJ@Z
// ($FA$_t_4a56f0)/add esp,4/ret. probe w13b_VietPaddy2.
extern void vietPaddy1X_(unsigned long a);

void T_VietRicePaddy3Proc(unsigned long a)
{
    vietPaddy1X_(a);
}