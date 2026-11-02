// ?SER_LeaveCriticalCodeForeground@@YAXXZ @ rva 0x4b170 (307568 DEC; off
// 304496) (32 B) — EXACT winner (probe w24c_SERLeaveCCF_v1.c). Pure CL C,
// NO patches. 0x1e body + census tail 8bff (2 B).
//
// FA asm: 68 <&Ctrl> / ff 15 __imp__EnterCriticalSection / c6 05 <Ctrl+0x1c>,0
// / 68 <&Ctrl> / ff 15 __imp__LeaveCriticalSection / ret.
//
// C recipe: dllimport stdcall externs give the ff 15 IAT calls (obj symbols
// __imp__X@4 — FA's IAT anchors lack the @4 so the map folds it); the
// interior byte store rides an extern char[] array element (addend in the
// C expression, no TO+delta needed).
//
// Maps (obj FROM -> FA name):
//   __imp__EnterCriticalSection@4=__imp__EnterCriticalSection
//   __imp__LeaveCriticalSection@4=__imp__LeaveCriticalSection
//   _serCtlQ=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_SERLeaveCCF_v1.obj 307568 \
//     build/survey/probes/w24c_SERLeaveCCF_v1_fit.obj \
//     --map '__imp__EnterCriticalSection@4=__imp__EnterCriticalSection' \
//     --map '__imp__LeaveCriticalSection@4=__imp__LeaveCriticalSection' \
//     --map '_serCtlQ=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A'
extern char serCtlQ[];   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */

__declspec(dllimport) void __stdcall EnterCriticalSection(void *a);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *a);

void SER_LeaveCCF_q(void)
{
    EnterCriticalSection(serCtlQ);
    serCtlQ[0x1c] = 0;
    LeaveCriticalSection(serCtlQ);
}