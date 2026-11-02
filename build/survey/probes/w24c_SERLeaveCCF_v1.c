// ?SER_LeaveCriticalCodeForeground@@YAXXZ @ rva 0x4b170 (32 B) — FA asm:
//   68 <&Ctrl>/ff 15 __imp__EnterCriticalSection / c6 05 <Ctrl+0x1c>,0 /
//   68 <&Ctrl>/ff 15 __imp__LeaveCriticalSection / ret / 8bff pad.  Twin of
//   the SER_Suspend/SER_Resume recipes: dllimport stdcall extern gives
//   the ff 15 IAT call and extern char[] array spelling the push-offset
//   argument; the interior byte store rides the map addend.
extern char serCtlQ[];   /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */

__declspec(dllimport) void __stdcall EnterCriticalSection(void *a);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *a);

void SER_LeaveCCF_q(void)
{
    EnterCriticalSection(serCtlQ);
    serCtlQ[0x1c] = 0;
    LeaveCriticalSection(serCtlQ);
}