/* w35F _GetKey2 @ 0x112f0 — v1
 * FA: 66 83 3d <kbCount> 00; push ebx; push esi; jne; eax=0 ret; push cs;
 * xor esi,esi; call Enter; 66 a1 <kbHeadPtr>; 66 ff 0d <kbCount> (dec);
 * mov ecx,eax; inc ax; and ecx,0xffff; mov si,[ecx*2+kbBuffer]; push cs;
 * and ax,0xf; 66 a3 <kbHeadPtr>; call Leave; mov eax,esi; pop esi; pop ebx; ret */
__declspec(dllimport) void __stdcall EnterCriticalSection(void *);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern unsigned short w35f_kcnt;   /* -> ?kbCount@@3GA */
extern unsigned short w35f_khead;  /* -> ?kbHeadPtr@@3GA */
extern unsigned short w35f_kbuf[]; /* -> ?kbBuffer@@3PAGA */
extern int w35f_kcs;               /* -> ?keyboard_critical_section@@3U_RTL_CRITICAL_SECTION@@A */

int __cdecl w35f_getkey2(void)
{
    unsigned short h, c;
    if (w35f_kcnt == 0)
        return 0;
    EnterCriticalSection((void *)&w35f_kcs);
    h = w35f_khead;
    w35f_kcnt--;
    c = w35f_kbuf[h & 0xffff];
    h++;
    w35f_khead = h & 0xf;
    LeaveCriticalSection((void *)&w35f_kcs);
    return c;
}
