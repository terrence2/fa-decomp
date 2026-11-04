// _G_ShutdownCircles@0 @ rva 0x69860 (48 B) — MMFreePtr over the 0x50-byte
//   pointer run at ?unAvailNames@@3PADA+0x24 (loop head is the load: mov
//   ecx,[esi] / add esi,4 / call), then a 0x50-byte memset of the same run.
//   do-while with the jb test keeps FA's cmp-imm32 / 72-ee re-entry.
#include <string.h>
extern char unAvailNames[];
extern void __fastcall MMFreePtr(void *p);
void __stdcall G_ShutdownCircles_q(void)
{
    void **p = (void **)(unAvailNames + 0x24);
    do
    {
        MMFreePtr(*p);
        p = (void **)((char *)p + 4);
    } while (p < (void **)(unAvailNames + 0x74));
    memset(unAvailNames + 0x24, 0, 0x50);
}