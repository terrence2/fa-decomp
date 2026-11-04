/* FA 0x4d39e0 _atol (164 B) — CRT band atol with MBCS gate (Isspace recipe) */
extern char ctype204[];                      /* __ctype+0x204 */
extern unsigned short pctype[];              /* __pctype */
extern int __cdecl isctypeQ(int c, int flg); /* __isctype */

long __cdecl atolQ(const char *str)
{
    long total;
    long ch;
    long dig;

    for (;;) {
        if (*(int *)ctype204 > 1) {
            if (isctypeQ((unsigned char)*str, 0x8) == 0) break;
        } else {
            if ((pctype[(unsigned char)*str] & 0x8) == 0) break;
        }
        ++str;
    }
    ch = *(unsigned char *)str;
    ++str;
    dig = ch;
    if (dig != '-') {
        if (dig == '+') {
            ch = *(unsigned char *)str;
            ++str;
        }
    } else {
        ch = *(unsigned char *)str;
        ++str;
    }
    total = 0;
    for (;;) {
        if (*(int *)ctype204 > 1) {
            if (isctypeQ((unsigned char)*str, 0x4) == 0) break;
        } else {
            if ((pctype[(unsigned char)*str] & 0x4) == 0) break;
        }
        total = total * 10 + (ch - '0');
        ch = *(unsigned char *)str;
        ++str;
    }
    if (dig == '-') total = -total;
    return total;
}