/* _SEQfadeout 0x45f30: fade start/end. a1==0: zero curPalette, G_SetPalette.
   else: copy curPalette->realPalette, seqFading=-1,
   seqFadeStart=timerTicks-seqIgnoreTicks, seqFadeLen=(a1<<8)/10, call tail. */
#include <string.h>

extern char curPalette[];                 /* _curPalette */
extern char realPalette[];                /* _realPalette */
extern short w44aSeqFadv;                 /* map: ?seqFading@@3FA */
extern unsigned long w44aTimerTr;         /* map: _timerTicks */
extern unsigned long w44aSeqIgnore;       /* map: ?seqIgnoreTicks@@3KA */
extern unsigned long w44aSeqFadeStart;    /* map: ?seqFadeStart@@3KA */
extern unsigned short w44aSeqFadeLen;     /* map: ?seqFadeLen@@3GA */
extern int __stdcall G_SetPalette(long pal, long a2, long a3, long a4);
extern void __cdecl w44aFadeTail(void *p);   /* map: _w44aFadeTail=$FA$_t_445d30 */

void __cdecl SEQfadeout(long a1)
{
    if (a1 == 0) {
        memset(curPalette, 0, 0x300);
        G_SetPalette((long)curPalette, 0, 0x100, 1);
        return;
    }
    memcpy(realPalette, curPalette, 0x300);
    w44aSeqFadv = -1;
    w44aSeqFadeStart = w44aTimerTr - w44aSeqIgnore;
    w44aSeqFadeLen = (unsigned short)(((long)a1 << 8) / 10);
    w44aFadeTail(&w44aSeqFadv);
}