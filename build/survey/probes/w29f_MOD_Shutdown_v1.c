// 0x99100 ?MOD_Shutdown@@YAXXZ — v1
__declspec(dllimport) void __stdcall Sleep(unsigned long ms);
extern void *volatile w29fModemField;   /* -> ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */
extern void *w29fMpiField;              /* -> ?mpInfo@@3UMP_INFO@@C+0x154 */
extern void __cdecl w29fSer1(void);
extern void __cdecl w29fSer2(void);
extern void __cdecl w29fSer3(void);
extern void __stdcall w29fHangup(void *p);
extern void __stdcall w29fAnswer(void *p, unsigned long a);

void __cdecl MOD_ShutdownX(void)
{
    if (w29fMpiField == 0)
        return;
    w29fSer1();
    Sleep(0x2ee);
    w29fHangup(w29fModemField);
    w29fAnswer(w29fModemField, 12);
    w29fSer2();
    w29fSer3();
}