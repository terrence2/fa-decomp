/* w43F 0x45eb0 v2: arm placement flip - if (n == 0) { GSP arm } else { fade
 * arm } so the GSP arm is INLINE (test ax / jne / else-block / ret) and the
 * fade arm is at the jne target, exactly as FA lays it out.
 */
#include <string.h>

extern void __stdcall w43F_GSP(void *a, long b, long c, long d);
extern void w43F_fdr(char *a);
extern unsigned char w43F_curPal[];     /* _curPalette */
extern unsigned char w43F_realPal[];    /* _realPalette */
extern unsigned long w43F_timerTicks;   /* _timerTicks */
extern unsigned long w43F_ignTicks;     /* ?seqIgnoreTicks@@3KA */
extern char w43F_seqFading;             /* ?seqFading@@3FA */
extern unsigned long w43F_seqFadeStart; /* ?seqFadeStart@@3KA */
extern short w43F_seqFadeLen;           /* ?seqFadeLen@@3GA */

void w43F_SEQfadein(unsigned short n)
{
    long t;
    if (n == 0) {
        w43F_GSP(w43F_curPal, 0, 0x100, 1);
    } else {
        memcpy(w43F_realPal, w43F_curPal, 768);
        *(short *)&w43F_seqFading = 1;
        t = (long)w43F_timerTicks - (long)w43F_ignTicks;
        w43F_seqFadeStart = t;
        w43F_seqFadeLen = (short)((n << 8) / 10);
        w43F_fdr(&w43F_seqFading);
    }
}
