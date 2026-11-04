/* PROJEngineState - FA rva 0xbd510 (775440) - EXACT probe verdict, tier1_a_r6.json entry 'PROJEngineState_v5'
 * Form: patch-hybrid
 * Levers: 7 patches: 66 a1 moffs load + FA operand order (sub,movsx,xor) vs CL (xor,sub,movsx)
 * Maps: _projTf=_curThing+0xe8, _projTpF=_curThingType+0xff, _projTpW=_curThingType+0x101, _currentT=_currentT
 * patch 0: 7->6 B 66 a1 9e 54 00, DIR32 re-add _currentT
 * patch 0x6: 2 B delete (33 c0)
 * patch 0x8: -> 05 (sub modrm)
 * patch 0xf: -> d0 (movsx edx)
 * patch 0x10: 0-offset insert 33 c0
 * patch 0x1b: -> 04 (jle disp)
 * patch 0x1c: 2->3 B 66 33 c0
 * Probes: v1-v6
 */
extern unsigned short currentT;
extern unsigned short projTf;
extern unsigned short projTpF;
extern unsigned short projTpW;

long __stdcall PROJEngineState(void)
{
    long d = (short)(currentT - projTf);
    if (projTpF > d)
        return 0;
    return (projTpW <= d) + 1;
}
