/* unnamed 0x65ae0 v2: alias-express reload of the brush slot (CSE-break),
   0x80B copy/memset sizes (rep movsd/stosd ecx=0x20). */
#include <string.h>

extern void *w44aCT110;     /* map: _w44aCT110=_curThing+0x110 */
extern void *w44aCT110b;    /* map: _w44aCT110b=_curThing+0x110 */
extern char w44aSvc28[];    /* map: _w44aSvc28=_serviceTicks+0x28 */
extern void *__fastcall MMAllocPtr(long size, long flag);

void __cdecl w44ac65ae0(void)
{
    if (w44aCT110 == 0) {
        w44aCT110 = MMAllocPtr(0x80, 0x8000);
    }
    memcpy(w44aCT110b, w44aSvc28, 0x80);
    memset(w44aSvc28, 0, 0x80);
}