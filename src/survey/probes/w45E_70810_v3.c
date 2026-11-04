/* FA 0x70810 v3: len staged as a local before i++ (FA schedules 43 90
 * [inc ebx + stall nop] between the scasb expansion and the lea edx);
 * hoping /G5 stall-padding reproduces FA's 90. */
#include <string.h>
extern int CHATGetEditLine(void);
extern int __fastcall Checksum(char *s, int len);
extern long w45E_brt80;

int w45E_70810_v3(void)
{
    char *s;
    int sum;
    long n, i, len;
    char *p;

    s = (char *)CHATGetEditLine();
    sum = 0;
    if (s)
        sum = Checksum(s, strlen(s));
    n = w45E_brt80;
    i = 0;
    if (n > i) {
        p = (char *)0x5426c8;
        do {
            len = strlen(p);
            i++;
            sum += Checksum(p, len);
            p += 0x79;
            n = w45E_brt80;
        } while (n > i);
    }
    return sum;
}
