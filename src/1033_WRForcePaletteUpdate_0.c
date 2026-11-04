// _WRForcePaletteUpdate@0 @ rva 0xb0aa0 — zero the 0x300-byte palette;
//   the known memset prototype makes CL 4.2 inline rep stosd (probe d85).
#include <string.h>

extern char lastPalette[];

void WRForcePaletteUpdate_q(void)
{
    memset(lastPalette, 0, 0x300);
}
