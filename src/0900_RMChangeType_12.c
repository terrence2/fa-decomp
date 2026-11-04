// w35C #1: _RMChangeType@12 @ rva 0xa3710 (128 B) — copy type string to buf,
// strrchr a '.', truncate, append s2. FA inlines strcpy/strcat/strlen
// (intrinsics); strrchr is a real out-of-line call (push . / push buf /
// call _strrchr / add esp,8). v1: plain C + library-extern strrchr.
#include <string.h>
extern char * __cdecl strrchrq(char *s, int c);

void __stdcall RMChangeType(char *s1, char *s2, char *buf)
{
    char *p;
    strcpy(buf, s1);
    p = strrchrq(buf, 0x2e);
    if (p)
        *p = 0;
    if (s2)
        strcat(buf, s2);
}