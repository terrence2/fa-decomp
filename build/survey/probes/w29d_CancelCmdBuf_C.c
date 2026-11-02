// v2C: goto shape — if (c==2) goto crqj; chain0; if (c!=4) goto retpoint;
// crqj: crq() tail jmp; retpoint falls into shared end ret.
extern volatile short w29d_w62;    /* _curThing+0x62 */
extern volatile short w29d_w58;    /* _curThing+0x58 */
extern char w29d_b50;              /* _curThing+0x50 */
extern char w29d_b51;              /* _curThing+0x51 */
extern short w29d_w54;             /* _curThing+0x54 */
extern short w29d_w52;             /* _curThing+0x52 */
extern char w29d_c0;               /* _curThing */
extern void __stdcall w29d_crq(void);

void __stdcall w29d_ccbC(void)
{
    unsigned char c;

    w29d_w62 = -1;
    w29d_w58 = -1;
    w29d_b50 = w29d_b51 = 7;
    c = w29d_c0;
    if (c == 2)
        goto crqj;
    w29d_w52 = w29d_w54 = 0;
    if (c != 4)
        goto retpoint;
crqj:
    w29d_crq();
    return;
retpoint:
    return;
}