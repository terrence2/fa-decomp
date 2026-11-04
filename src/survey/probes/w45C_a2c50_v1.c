extern char *w45c_ctab[];    /* _campaignPilot+0xbd8 */
extern char *w45c_ftab[];    /* _fmtReduceButtonH+0x730 */
extern char w45c_fmt[];      /* ?wsa_string2@@3PAPADA+0x1e4 */
extern char w45c_err[];      /* _stats+0x1c28 */
extern char *w45c_sprintf(char *, char *, long);   /* _Sprintf */

char *w45C_a2c50(long x)
{
    if (x >= 0x2710 && x <= 0x2775)
        return (char *)w45c_ctab[x];
    if (x >= 0x2af9 && x <= 0x2afc)
        return (char *)w45c_ftab[x];
    w45c_sprintf(w45c_err, w45c_fmt, x);
    return w45c_err;
}