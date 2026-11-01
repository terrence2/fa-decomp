// ?T_VietWaterBuffaloProc@@YAXJ@Z @ rva 0xa58d0 (16 B, FPO fpo/esp) —
// forwards the long (cattle id?) to T_MooseProc: mov eax,[esp+4] / push
// eax / call / add esp,4 / ret / 8bff pad. Statement call (not a tail —
// FA emits call+cleanup, probe w13c_vwb1 exact).
extern void T_MooseProc(long t);

void T_VietWaterBuffaloProc(long t)
{
    T_MooseProc(t);
}