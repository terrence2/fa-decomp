/* probe v1 */
extern unsigned long _mbcgA;    /* __mbcgA -> __mbctype+0x104 */
extern unsigned long _mbcgB;    /* __mbcgB -> __mbctype+0x108 */
extern int _collw(unsigned long g2, int flag, const unsigned char *x,
                  unsigned int count, const unsigned char *x2,
                  unsigned int count2, unsigned long g1);
/* obj _collw -> $FA$_t_4e0500 */

int _mbsnbcoll_q(const unsigned char *str1, const unsigned char *str2,
                 unsigned int count)
{
    int r;
    if (count == 0)
        return 0;
    r = _collw(_mbcgB, 1, str2, count, str2, count, _mbcgA);
    if (r == 0)
        return 0x7fffffff;
    return r - 2;
}
