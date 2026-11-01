// _CTInit@0 @ rva 0x63e20 (24 B) — byte-clear at _serviceTicks+0x104 lands
//   between the memset count setup (mov ecx,0x20) and rep stosd; CL's
//   scheduler places the independent c6 05 store in that slot (probe d126,
//   memset-first order loses push edi and the slot, d127).
#include <string.h>
extern char serviceTicks[];
void __stdcall CTInit_q(void)
{
    serviceTicks[0x104] = 0;
    memset(serviceTicks + 0x28, 0, 0x80);
}
