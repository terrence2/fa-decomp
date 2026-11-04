/* w42B 0x64fe0 _CTDo_movetoalt (128 B) v2 — signed long clamp (jg/jge),
 * decl order (a, d, b, e) so VC's [esi,edi,ebx] pool gives a=esi, d=edi,
 * b=ebx as FA does. */
extern char serviceTicks[];
extern char curThingType[];
extern int w42b_f00(void);   /* -> $FA$_t_464f00 */
extern int w42b_c90(void);   /* -> $FA$_t_464c90 */
extern int w42b_fc0(void);   /* -> $FA$_t_464fc0 */
extern int w42b_fa0(void);   /* -> $FA$_t_464fa0 */
extern void __stdcall MVRMoveToAltQ(unsigned short a, unsigned long b,
                                    unsigned short x, unsigned short y,
                                    unsigned short d, unsigned long e);
     /* map _MVRMoveToAltQ@24=_MVRMoveToAlt@24 */

void CTDo_movetoalt(void)
{
    unsigned short a;
    unsigned short d;
    long b;
    unsigned long e;
    long u1;
    long u2;

    a = (unsigned short)w42b_f00();
    b = w42b_c90() << 8;
    u1 = *(long *)(curThingType + 0x75);
    if (u1 > b)
        b = u1;
    else {
        u2 = *(long *)(curThingType + 0x79);
        if (u2 < b)
            b = u2;
    }
    d = (unsigned short)w42b_fc0();
    e = w42b_fa0();
    if (serviceTicks[0xec])
        return;
    MVRMoveToAltQ(a, b, *(unsigned short *)(serviceTicks + 0xfc),
                  *(unsigned short *)(serviceTicks + 0x100), d, e);
    *(unsigned short *)(serviceTicks + 0x100) = 0;
    *(unsigned short *)(serviceTicks + 0xfc) = 0;
    serviceTicks[0xf0] = 1;
    serviceTicks[0xf8] = 1;
}