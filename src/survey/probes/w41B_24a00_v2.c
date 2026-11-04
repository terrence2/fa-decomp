/* w41B 0x24a00 v2: fixed CLR label; signed long m with imm8 masks. */
unsigned long __fastcall w41bBit24(char *p)
{
    unsigned long *a;
    unsigned long d;
    long m;
    unsigned long rv;

    a = *(unsigned long **)(p + 5);
    d = *(unsigned char *)a;
    if (d == 5)
        goto SET;
    if (d == 7)
        goto SET;
    if (d != 3)
        goto CLR;
    if (*(long *)(p + 0xe8) != 0)
        goto SET;
CLR:
    m = *(long *)(p + 1);
    m = m & -5;
    goto ST;
SET:
    m = *(long *)(p + 1);
    m = m | 4;
ST:
    p = p + 1;
    *(long *)p = m;

    if (d == 5)
        goto SET2;
    if (d == 3)
        goto SET2;
    if (*(unsigned long *)((char *)a + 9) & 0x8000)
        goto SET2;
    rv = *(long *)p;
    rv = rv & -3;
    *(long *)p = rv;
    return rv;
SET2:
    rv = *(long *)p;
    rv = rv | 2;
    *(long *)p = rv;
    return rv;
}