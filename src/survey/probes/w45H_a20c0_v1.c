/* w45H 0xa20c0: fastcall percent formatter ("NN%") with "-" sentinel */
typedef unsigned long ulong;

char *strcpy(char *, const char *);
char * __cdecl sprintf(char *, const char *, ...);
extern char hudslewDash;    /* _hudslewDash = ?hudslewLimitHdg@@3UWORD_POINT@@A (+0x23c) */
extern char ifmShowTxt;     /* _ifmShowTxt  = ?ifmShow@@3GA (+0x22c) */

char * __fastcall w45H_a20c0(int a, int b, char *dst)
{
    if (b == 0) {
        strcpy(dst, "-");
        return dst;
    }
    if (a < 0)
        a = 0;
    else if (a > b)
        a = b;
    sprintf(dst, (const char *)((char *)&ifmShowTxt + 0x22c), (a * 100) / b);
    return dst;
}