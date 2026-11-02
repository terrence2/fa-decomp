/* lockerr_exit - FA rva 0xd72e0 (881376) - EXACT probe verdict, tier1_a_r3.json entry 'lockerr_exit_v1'
 * Form: patch-hybrid
 * Levers: patch tail: FF 15 imp-call form replaces CL push/mov frames
 * Maps: __imp__FatalAppExitA=__imp__FatalAppExitA, __imp__ExitProcess=__imp__ExitProcess
 * patch 4: tail 27->21 B: 68..ff 15..c3 imp-call form, DIR32 re-adds 2 imp syms
 * Probes: v1
 */
void __declspec(dllimport) __stdcall FatalAppExitA(unsigned a, char *b);
void __declspec(dllimport) __stdcall ExitProcess(unsigned c);

void lockerr_exit_q(char *msg)
{
    FatalAppExitA(0, msg);
    ExitProcess(255);
}
