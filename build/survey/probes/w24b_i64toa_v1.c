/* probe v1: __i64toa wrapper — radix/neg diamond + 5-arg worker tail call */
typedef unsigned __int64 T64;
extern char *_i64toa_w(unsigned int lo, unsigned int hi, char *buf,
                       int radix, int neg);
                       /* obj __i64toa_w -> $FA$_t_4e2000 */

char *_i64toa_q(T64 val, char *buf, int radix)
{
    int neg;
    neg = radix == 10 && (__int64)val < 0;
    _i64toa_w((unsigned int)val, (unsigned int)(val >> 32), buf, radix, neg);
    return buf;
}
