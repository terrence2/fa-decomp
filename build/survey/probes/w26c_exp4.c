// exp4: HUD h8/h9 combos; SN fastcall spellings (sv6 forgot __fastcall)
extern int w26_hudBright; /* map _w26_hudBright=?hudBrightness@@3JA */

/* h8: h5 header (e local, +=) + h6 tail (ternary-chain on the global) */
void __fastcall w26c_HUD_h8(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright = w26_hudBright + e;
    w26_hudBright = (w26_hudBright < -0x100) ? 0xffffff00 : w26_hudBright;
    w26_hudBright = (w26_hudBright > 0x100) ? 0x100 : w26_hudBright;
}

/* h9: h5 header + if-else arms spelling */
void __fastcall w26c_HUD_h9(unsigned char p1)
{
    int e, n;
    e = (p1 < 1) ? -16 : 16;
    n = w26_hudBright + e;
    w26_hudBright = n;
    if (n < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    w26_hudBright = n;
    if (n > 0x100)
        w26_hudBright = 0x100;
}

/* ---- SN sv8: __fastcall short param ---- */
extern unsigned char w26_soundOn; /* map _w26_soundOn=_soundOn */
extern unsigned char w26_sndDefA[]; /* map _w26_sndDefA=$FA$_d_4e7000+0x548 */
extern unsigned char w26_MODpA[]; /* map _w26_MODpA=?MOD@@3PAUMODSPEC@@A */
extern unsigned char w26_specialsA[]; /* map _w26_specialsA=_specials+0xb30 */

char * __fastcall w26c_SN_sv8(short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    if (p1 < (short)16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}

/* sv9: __fastcall unsigned short p1 */
char * __fastcall w26c_SN_sv9(unsigned short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    if (p1 < 16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}