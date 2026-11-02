/* @DialogGetValue@4 @ 0x87420 — v1: switch with default-first source order */
extern void *__fastcall w28b_DialogGetPtr(void *arg);    /* -> @DialogGetPtr@4 */

short __fastcall DialogGetValue_dg(void *arg)
{
    unsigned long n;
    unsigned char *p = (unsigned char *)w28b_DialogGetPtr(arg);
    n = (*(unsigned short *)p & 0x7fff) - 3;
    switch (n) {
    default:
    case 2:
        return 0;
    case 0:
        return (short)(signed char)p[0x16];
    case 1:
        return (short)*(unsigned short *)(p + 0x1a);
    case 3:
        return (short)*(unsigned short *)(p + 0x20);
    case 4:
        return (short)*(unsigned short *)(p + 0xc);
    case 5:
        return (short)(signed char)p[0x1e];
    }
}
