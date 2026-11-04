extern long w35a_ctget(void);  /* -> $FA$_t_464c90 */

long w35a64f60(void)
{
    long t;
    t = w35a_ctget();
    if (t != 0x7fffffff) {
        if (t > 180) t = 180;
        if (t < -180) t = -180;
        t = t * 182;
    }
    return t;
}
