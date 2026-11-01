// _APInit@0 @ rva 0xb6b80 — zero the airport records (0x870 bytes past
//   +0x3020) and clear the count; the word store lands in the memset
//   scheduler slot (numAirports-first order, CTInit pattern d126/d158)
#include <string.h>
extern char airports[];
extern unsigned short numAirports;
void __stdcall APInit_q(void)
{
    numAirports = 0;
    memset(airports + 0x3020, 0, 0x870);
}
