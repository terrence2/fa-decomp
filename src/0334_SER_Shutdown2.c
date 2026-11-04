/* w46B_sershutdown2_v3 - ?SER_Shutdown2@@YAXXZ, FA rva 0x4c220 (311840), 112 B, tail 8bff (2-B census filler)
 * cdecl, FPO cbRegs=4, one esp local (exit code, [esp+0x10] after pushes).
 * FA .reloc sites (page walk): 4,13,19,1f,2f,44,4b,50,56,5c (all HIGHLOW).
 * anchors: ?mpInfo@@3UMP_INFO@@C @0x4fbb90 (+0x154 flag dword),
 *          ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A @0x5680e8 (+0x1d byte=1, +0x18 hThread
 *          =0x568100 read/compare-while-active/zeros to NULL, push of struct base for
 *          DeleteCriticalSection), IATs Sleep/GetExitCodeThread via esi/edi reg-indirect,
 *          CloseHandle direct ff15, DeleteCriticalSection via ebp reg-indirect.
 */
extern void __declspec(dllimport) __stdcall Sleep(unsigned long);
extern unsigned long __declspec(dllimport) __stdcall GetExitCodeThread(void *h, unsigned long *code);
extern int __declspec(dllimport) __stdcall CloseHandle(void *h);
extern void __declspec(dllimport) __stdcall DeleteCriticalSection(void *cs);
extern unsigned char mpI_[0x200];      /* ?mpInfo@@3UMP_INFO@@C */
extern unsigned char Ctrl_[0xf0];      /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */

void SER_Shutdown2(void)
{
    void (__stdcall *pSleep)(unsigned long);
    unsigned long (__stdcall *pGect)(void *, unsigned long *);
    unsigned long sa;
    void (__stdcall *pDel)(void *);
    unsigned long code;

    pSleep = Sleep;
    pGect = GetExitCodeThread;
    if (*(long *)(mpI_ + 0x154))
    {
        *(unsigned char *)(Ctrl_ + 0x1d) = 1;
        sa = 0x103;
        for (;;)
        {
            pGect(*(void **)(Ctrl_ + 0x18), &code);
            if (code != sa) break;
            pSleep(0);
        }
        CloseHandle(*(void **)(Ctrl_ + 0x18));
        pDel = DeleteCriticalSection;
        *(void **)(Ctrl_ + 0x18) = 0;
        pDel((void *)(Ctrl_));
    }
}