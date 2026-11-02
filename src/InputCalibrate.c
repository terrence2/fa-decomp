/* InputCalibrate - FA rva 0x175e0 (95712) - EXACT probe verdict, tier1_a_r1.json entry 'InputCalibrate_v1'
 * Form: plain C
 * Levers: plain C
 * Maps: _deviceProcs=?deviceProcs@@3PAP6AFFF@ZA, _mouseShown=?mouseShown@@3FA, _ShellShowMouse@0=?ShellShowMouse@@YGXXZ
 * Probes: v1
 */
typedef short (__cdecl *DEVPROC)(short a);
extern DEVPROC deviceProcs[];
extern short mouseShown;
extern void __stdcall ShellShowMouse(void);

void InputCalibrate(short v)
{
    deviceProcs[v](1);
    while (mouseShown <= 0)
        ShellShowMouse();
}
