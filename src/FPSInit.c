// _FPSInit @ rva 0x84e40 (32 B) — 10-dword zero fill at _timeCompression+8
//   (rep stosd from the inline memset), then _timerTicks copied into
//   _currentT+0x10 and _frameTicks+0x4 via a3 moffs stores.
#include <string.h>
extern char timeCompression[];
extern long timerTicks;
extern char currentT[];
extern char frameTicks[];
void FPSInit_q(void)
{
    long t;
    memset(timeCompression + 8, 0, 40);
    t = timerTicks;
    *(long *)(currentT + 0x10) = t;
    *(long *)(frameTicks + 0x4) = t;
}