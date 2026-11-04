/* w38C 0xd4f50 (45 B) v3: decl y (arg2) first, x (arg1) second — FA loads
 * arg2 to edx first, arg1 to ecx between the pushes, cmp edx,ecx. */
void w38c_d4f50(void *p1, void *p2, unsigned int n)
{
    char *y = (char *)p2;
    char *x = (char *)p1;
    char t;

    if (x == y)
        return;
    while (n-- != 0) {
        t = *x;
        *x = *y;
        *y = t;
        x++;
        y++;
    }
}