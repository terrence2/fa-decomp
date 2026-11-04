// ?dlg_list_get_selection@@YA?AW4DLG_SELECTION@@PAXPAUNET_ADDRESS@@PAD@Z v4 —
// named locals (d0/d1/d2/w3 force FA's len-temp colors) + rec != 0 wrapper
// (v2's shape gave CL's je-forward-to-end return-0 = FA's 85c9/7463).
#include <string.h>

long __cdecl w43b_dlgsel4(void *p, void *addr, char *str)
{
    char *rec;
    unsigned long d0;
    unsigned long d1;
    unsigned long d2;
    unsigned short w3;

    rec = *(char **)((char *)p + 4);
    if (rec != 0) {
        d0 = *(unsigned long *)((char *)rec + 0x2a);
        rec = rec + 0x2a;
        *(unsigned long *)addr = d0;
        d1 = *(unsigned long *)((char *)rec + 4);
        *(unsigned long *)((char *)addr + 4) = d1;
        d2 = *(unsigned long *)((char *)rec + 8);
        *(unsigned long *)((char *)addr + 8) = d2;
        w3 = *(unsigned short *)((char *)rec + 0xc);
        *(unsigned short *)((char *)addr + 0xc) = w3;
        strcpy(str, *(char **)((char *)p + 4));
        if (*(char *)((char *)p + 0x19)) {
            *(char *)((char *)p + 0x19) = 0;
            return 1;
        }
        return 2;
    }
    return 0;
}