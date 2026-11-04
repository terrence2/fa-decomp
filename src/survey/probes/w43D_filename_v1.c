/* 0x700c0 ?MPSingleFilename@@YIXPAD@Z 0x60 */
#include <string.h>
extern unsigned long numComputers;
extern void __fastcall w43D_mpflush(char n);
extern void __stdcall w43D_snd(long id, void *msg, long size, long flag);

void __fastcall w43D_single(char *fn)
{
    char m[16];
    if (numComputers == 1)
        return;
    m[0] = 0x40;
    strcpy(m + 1, fn);
    w43D_snd(-1, m, 0xe, 1);
    w43D_mpflush(1);
}
