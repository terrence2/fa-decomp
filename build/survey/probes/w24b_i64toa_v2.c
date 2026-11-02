/* probe v2: worker as __stdcall with 64-bit first arg */
typedef unsigned __int64 T64;
extern char *__stdcall _i64toa_w(T64 val, char *buf, int radix, int neg);
/* obj __imp? plain: _i64toa_w@20 -> $FA$_t_4e2000 */

char *_i64toa_q(T64 val, char *buf, int radix)
{
    int neg;
    neg = radix == 10 && (__int64)val < 0;
    _i64toa_w(val, buf, radix, neg);
    return buf;
}
