// ?SER_Shutdown1@@YAXXZ @ rva 0x4c1f0 = 311792, 48 B (cdecl void; gate on
// ?mpInfo+0x154; byte store ?Ctrl+0x12b=1; dword store ?Ctrl+0x218=0;
// Sleep(0x12c) via ff 15 __imp__Sleep; tail e9 jmp SER_ShutdownLowLevel).
extern int w26_mpOn1; /* map _w26_mpOn1=?mpInfo@@3UMP_INFO@@C+0x154 */
extern unsigned char w26_ctrlB12b; /* map _w26_ctrlB12b=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12b */
extern unsigned long w26_ctrlD218; /* map _w26_ctrlD218=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x218 */
extern void __cdecl SER_ShutdownLowLevelQ(void); /* map _SER_ShutdownLowLevelQ=?SER_ShutdownLowLevel@@YAXXZ */
__declspec(dllimport) void __stdcall Sleep(unsigned long n);

void __cdecl w26c_SER_Shutdown1_q(void)
{
    if (w26_mpOn1) {
        w26_ctrlB12b = 1;
        w26_ctrlD218 = 0;
        Sleep(0x12c);
        SER_ShutdownLowLevelQ();
    }
}