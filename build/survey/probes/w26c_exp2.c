// variants: HUD if/else spelling; GCP decl/use orders; Ukraine decl swap;
// SoundName array externs + raw-param compare; PotRudder array extern
typedef struct { unsigned char pad[8]; short fx, fy, fw, fh; } D26u;

/* ---- HUDBrightness: int n local, if/else clamps ---- */
extern unsigned long w26_hudBright; /* map _w26_hudBright=_hudBright */

void w26c_HUD_h3(unsigned char f)
{
    int n = (int)w26_hudBright + ((f < 1) ? -16 : 16);
    if (n < -256)
        w26_hudBright = 0xffffff00;
    else
        w26_hudBright = (unsigned long)n;
    if (n > 256)
        w26_hudBright = 0x100;
}

void w26c_HUD_h4(unsigned char f)
{
    int e = (f < 1) ? -16 : 16;
    int n = (int)w26_hudBright + e;
    if (n < -256)
        w26_hudBright = 0xffffff00;
    else
        w26_hudBright = (unsigned long)n;
    if (n > 256)
        w26_hudBright = 0x100;
}

/* ---- GetContactPositions: pd declared LAST ---- */
extern int w26_numContactsQ; /* map _w26_numContactsQ=?numContacts@@3JA */
extern void *w26_objPtrsQ[]; /* map _w26_objPtrsQ=_objPtrs */
extern unsigned short __cdecl CPGetContactQ(int n); /* map _CPGetContactQ=?CPGetContact@@YGGJ@Z */
extern int __stdcall GRTo2dQ(unsigned int id, void *dst); /* map _GRTo2dQ@8=_GRTo2d@8 */

void __fastcall w26c_GCP_g4(unsigned int *o)
{
    int i;
    unsigned short c;
    unsigned int *pd;
    for (i = 0; i < w26_numContactsQ; i++) {
        c = CPGetContactQ(i);
        if (c == 0) {
            *(unsigned short *)&o[i] = 0x8000;
            continue;
        }
        pd = (unsigned int *)&o[i];
        if (GRTo2dQ((unsigned int)w26_objPtrsQ[c] + 0x11, pd))
            *(unsigned short *)pd = 0x8000;
    }
}

/* gv5: no named pd; address expression inline twice (CSE temp) */
void __fastcall w26c_GCP_g5(unsigned int *o)
{
    int i;
    unsigned short c;
    for (i = 0; i < w26_numContactsQ; i++) {
        c = CPGetContactQ(i);
        if (c == 0) {
            *(unsigned short *)&o[i] = 0x8000;
            continue;
        }
        if (GRTo2dQ((unsigned int)w26_objPtrsQ[c] + 0x11, &o[i]))
            *(unsigned short *)&o[i] = 0x8000;
    }
}

/* gv8: condition spelled numContacts > i */
void __fastcall w26c_GCP_g8(unsigned int *o)
{
    int i;
    unsigned short c;
    unsigned int *pd;
    for (i = 0; w26_numContactsQ > i; i++) {
        c = CPGetContactQ(i);
        if (c == 0) {
            *(unsigned short *)&o[i] = 0x8000;
            continue;
        }
        pd = (unsigned int *)&o[i];
        if (GRTo2dQ((unsigned int)w26_objPtrsQ[c] + 0x11, pd))
            *(unsigned short *)pd = 0x8000;
    }
}

/* ---- Ukraine: decl (walker, count, best, max) ---- */
extern unsigned char w26_rankStr[]; /* map _w26_rankStr=_pilotRanks+0x1ec */
extern unsigned char w26_campArr[]; /* map _w26_campArr=_campaignPilot+0xdb0 */
extern int __cdecl strnicmpQ(const void *s1, const void *s2, unsigned int n); /* map _strnicmpQ=_strnicmp */
extern void *__cdecl memset(void *d, int c, unsigned int n); /* intrinsic - no map */

void w26c_UA_u3(void)
{
    unsigned char *walker;
    int count;
    unsigned long best;
    int max;
    do {
        count = 0;
        walker = (unsigned char *)w26_campArr;
        best = 0;
        max = 0;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    int r;
                    r = *(short *)(walker + 0x2e);
                    if (r >= max) {
                        max = r;
                        best = (unsigned long)walker;
                    }
                }
            }
            walker += 0xbc;
        } while ((unsigned long)walker < 0x4f6778);
        if (count <= 11)
            break;
        --count;
        memset((void *)best, 0, 188);
    } while (count > 11);
}

/* u5: same but count -= 1 spelling */
void w26c_UA_u5(void)
{
    unsigned char *walker;
    int count;
    unsigned long best;
    int max;
    do {
        count = 0;
        walker = (unsigned char *)w26_campArr;
        best = 0;
        max = 0;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    int r;
                    r = *(short *)(walker + 0x2e);
                    if (r >= max) {
                        max = r;
                        best = (unsigned long)walker;
                    }
                }
            }
            walker += 0xbc;
        } while ((unsigned long)walker < 0x4f6778);
        if (count <= 11)
            break;
        count -= 1;
        memset((void *)best, 0, 188);
    } while (count > 11);
}

/* ---- SoundName: array externs + p1 compared directly ---- */
extern unsigned char w26_soundOn; /* map _w26_soundOn=_soundOn */
extern unsigned char w26_sndDefA[]; /* map _w26_sndDefA=$FA$_d_4e7000+0x548 */
extern unsigned char w26_MODpA[]; /* map _w26_MODpA=?MOD@@3PAUMODSPEC@@A */
extern unsigned char w26_specialsA[]; /* map _w26_specialsA=_specials+0xb30 */

char *w26c_SN_s3(unsigned short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    if (p1 < 16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}

/* sv4: compare 16-bit via local short */
char *w26c_SN_s4(short p1)
{
    short c;
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    c = p1;
    if (c < 16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}

/* sv5: condition 0x10 literal spelled (short) */
char *w26c_SN_s5(short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    if (p1 < (short)16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}

/* ---- PotRudder: rudder as array extern (push imm32) ---- */
extern void *w26_rudderArr[]; /* map _w26_rudderArr=_rudder */
extern void __fastcall NormalizeStickQ(unsigned int a, unsigned int b,
                                       unsigned int *c1, void *c2); /* map @NormalizeStickQ@16=@NormalizeStick@16 */
extern short w26_rudderVal;

short w26c_PR_p3(unsigned int p1, unsigned int p2)
{
    int c = p1;
    short r;
    switch (c) {
    case 2:
        NormalizeStickQ(0, 0, 0, (void *)w26_rudderArr);
        r = w26_rudderVal;
        break;
    case 3:
        r = (short)p2;
        break;
    default:
        r = 0;
        break;
    }
    return r;
}