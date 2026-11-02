/* probe v3: signed 64-bit param, 3-stage mem-compare diamond */
typedef __int64 T64;
extern char *__stdcall _i64toa_w(T64 val, char *buf, int radix, int neg);

char *_i64toa_q(T64 val, char *buf, int radix)
{
    int neg;
    neg = radix == 10 && val < 0;
    _i64toa_w(val, buf, radix, neg);
    return buf;
}
