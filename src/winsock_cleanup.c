// ?winsock_cleanup@@YAXXZ @ rva 0xa2b50 (48 B) — call [ws+0xa] (ff 15);
// if [ws+0x2] >= 0x20 FreeLibrary(eax); memset(ws, 0, 0x66) inline
// (mov edi,imm; xor eax; mov ecx,0x19; rep stosd; stosw).
#include <string.h>
extern char w27a_wsB[];                    /* ?ws@@3U_winsock_funcs@@A */
extern void (__cdecl *w27a_wsA)(void);     /* ?ws@@3U_winsock_funcs@@A+0xa */
extern unsigned int w27a_ws2;              /* ?ws@@3U_winsock_funcs@@A+0x2 */
void __declspec(dllimport) __stdcall FreeLibraryQ(void *h);
void w27a_wsc_q(void)
{
    w27a_wsA();
    if (w27a_ws2 >= 0x20)
        FreeLibraryQ((void *)w27a_ws2);
    memset(&w27a_wsB[0], 0, 0x66);
}