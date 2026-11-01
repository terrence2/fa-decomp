// @flushLineStats@0 @ rva 0x5d9a0 (48 B) — movsx word grMode+0xc (count),
// then CL 4.2's inline memcpy: count parked in eax, rep movsd (shr ecx,2)
// + rep movsb (and ecx,3) with esi=src/edi=dst, pop/pop/ret. Plain C
// memcpy reproduces it exactly (probe w14a_fls1; the hand-rolled rep-movs
// asm w14a_fls2 is identical).
#include <string.h>

extern short grModeW;              // _grMode+0xc (word)
extern char lineStats[];
extern char visibleLineStats[];

void __fastcall flushLineStats(void)
{
    memcpy(visibleLineStats, lineStats, (unsigned)(int)grModeW);
}