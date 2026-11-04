/* 0xda510 (unnamed, 56 B): cdecl(int flag, void *s); bit 0x10 test on
 * s->+0xd; then sub(s), and s->+0xc &= 0xffffeeff, zero +0x18/+0/+8,
 * with the call cleanup (add esp,4) deferred past the +0x18 store. */
extern void w38a_sub(void *s);    /* $FA$_t_4d5f30 */

void w38a_da510(int flag, void *s)
{
    unsigned char *b = (unsigned char *)s;
    unsigned long *lo = (unsigned long *)s;
    if (flag == 0)
        return;
    if (!(*(b + 0xd) & 0x10))
        return;
    w38a_sub(s);
    lo[3] &= 0xffffeeff;
    lo[6] = 0;
    lo[0] = 0;
    lo[2] = 0;
}
