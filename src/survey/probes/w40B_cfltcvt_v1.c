/* rva 0xd9890 (dec 891024), 101 B __cfltcvt - type dispatch for printf %e/%f/%g.
 * v1: plain if/or/else-if chain, prototyped externs.
 */
extern void __cftof(void *val, char *buf, int prec);
extern void __cftog(void *val, char *buf, int prec, int caps);
extern void __cftoe(void *val, char *buf, int prec, int caps);

void cfltcvt0(void *val, char *buf, int type, int prec, int caps)
{
    if (type == 'e' || type == 'E')
        __cftoe(val, buf, prec, caps);
    else if (type == 'f')
        __cftof(val, buf, prec);
    else
        __cftog(val, buf, prec, caps);
}