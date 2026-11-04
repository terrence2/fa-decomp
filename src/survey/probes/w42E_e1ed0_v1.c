/* w42E candidate 5: unnamed chunk @ rva 0xe1ed0 (925392, 60 B) — itoa-family
 * neg-precalc wrapper: f(a1, a2, a3, flag) with flag=1 iff radix==10 && val<0;
 * returns str (esi). helper $FA$_t_4e1f10 (still-stub) = __ltoa/__ultoa core.
 */
extern long w42E_int2str(long val, char *str, long radix, long neg);

char *w42E_e1ed0_v1(long val, char *str, long radix)
{
    if (radix == 10 && val < 0) {
        w42E_int2str(val, str, radix, 1);
        return str;
    }
    w42E_int2str(val, str, radix, 0);
    return str;
}