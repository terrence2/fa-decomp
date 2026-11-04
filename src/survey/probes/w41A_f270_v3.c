/* wave-41A probe v3: 0x40f270 — do-while (no rotated entry test, no edi save). */
extern void *w41a_tbl8[];           /* ?remapDarken320@@3PAEA+0x118 = VA 0x4e83e8 */
extern unsigned char *w41a_tend[];  /* ?remapDarken320@@3PAEA+0x138 = VA 0x4e8408 */
extern void *w41a_tbldef;           /* ?remapDarken320@@3PAEA+0x120 = VA 0x4e83f0 */

void * __fastcall w41a_f270(void *val, int d)
{
    void **p;
    int i;

    p = w41a_tbl8;
    i = 0;
    do {
        if (*p == val) {
            i += d;
            if (i < 0) i = 0;
            else if (i > 7) i = 7;
            return w41a_tbl8[i];
        }
        p++;
        i++;
    } while (p < (void **)w41a_tend);
    return w41a_tbldef;
}