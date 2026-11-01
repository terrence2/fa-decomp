// _G_InitLineStats@0 @ rva 0x955c0 (48 B) — two inline memset(0xff) fills of
//   0x12d*4+1 = 1205 B over _lineStats and _visibleLineStats (mov eax,-1 /
//   mov edi,m / mov ecx,0x12d / rep stosd + stosb each), single push/pop edi.
#include <string.h>
extern char lineStats[];
extern char visibleLineStats[];
void __stdcall G_InitLineStats_q(void)
{
    memset(lineStats, 0xff, 1205);
    memset(visibleLineStats, 0xff, 1205);
}