/* 0xa23c0 (unnamed, 80 B): thiscall(fastcall-with-ecx); dot = strchr(s,'.');
 * Strend; strip trailing '0's back to dot; then strip a bare trailing '.'. */
extern char *w38a_strchr(char *s, int ch);   /* _strchr */
extern char * __fastcall w38a_strend(char *s);   /* @Strend@4 */

void __fastcall w38a_a23c0(char *s)
{
    char *dot = w38a_strchr(s, 0x2e);
    char *p;
    char c;
    if (dot == 0)
        return;
    p = w38a_strend(s);
    for (;;) {
        c = *(p - 1);
        p = p - 1;
        if (c != 0x30)
            break;
        if (p < dot)
            break;
        *p = 0;
        c = *(p - 1);
        p = p - 1;
        if (c != 0x30)
            break;
    }
    if (*p == 0x2e)
        *p = 0;
}
