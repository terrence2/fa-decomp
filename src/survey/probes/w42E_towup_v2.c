/* w42E candidate 3 v2: table global spelled as a mapped dword public
 * (w42E_c388=__ctype+0x388) for the cmp m32,0 + call arg, iswctype arg via
 * int-slice *(int*)&c to kill CL's ushort->int and-mask, multi-call polarity
 * as `if (f(...) == 0) return c; return tmp;` for FA's jne-to-tmp.
 */
extern int iswctype(int c, int mask);
extern unsigned long w42E_c388;
extern long w42E_widemap(void *tbl, long len, void *c, long a, void *tmp, long b, long z);

unsigned short __cdecl _towupper_lk(unsigned short c)
{
    unsigned short tmp;

    if (c == 0xFFFF)
        return c;
    if (w42E_c388 == 0) {
        if (c >= 'a' && c <= 'z')
            c -= 0x20;
        return c;
    }
    if (c < 0x100) {
        if (!iswctype(*(int *)&c, 2))
            return c;
    }
    if (w42E_widemap((void *)w42E_c388, 0x200, &c, 1, &tmp, 1, 0) == 0)
        return c;
    return tmp;
}