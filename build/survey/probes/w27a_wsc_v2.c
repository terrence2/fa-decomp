// winsock_cleanup — inline-asm escape hatch supplies FA's unused-ebx save
// (53 prologue / 5b epilogue) around CL's own edi-based body.
#include <string.h>
extern char w27a_wsB[];
extern void (__cdecl *w27a_wsA)(void);
extern unsigned int w27a_ws2;
void __declspec(dllimport) __stdcall FreeLibraryQ(void *h);
void w27a_wsc_q(void)
{
    __asm { push ebx }
    w27a_wsA();
    if (w27a_ws2 >= 0x20)
        FreeLibraryQ((void *)w27a_ws2);
    memset(&w27a_wsB[0], 0, 0x66);
    __asm { pop ebx }
}
