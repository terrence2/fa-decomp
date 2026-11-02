/* GG_WaitRetrace - FA rva 0x5da40 (383552) - EXACT probe verdict, tier1_a_r1.json entry 'GG_WaitRetrace_v1.c'
 * Form: plain C
 * Levers: wave-21 thiscall idiom: .cpp plain class member + __stdcall fn-ptr typedef
 * Maps: _ddInst=?ddInst@@3PAVCDirDraw@@A, _CDirDraw_WVB=?WaitForVerticalBlank@CDirDraw@@QAEXK@Z
 * Probes: v1
 */
class CDirDraw {
public:
    void WaitForVerticalBlank(unsigned long a);
};
extern "C" CDirDraw *ddInst;

extern "C" void GG_WaitRetrace(void)
{
    if (ddInst)
        ddInst->WaitForVerticalBlank(1);
}
