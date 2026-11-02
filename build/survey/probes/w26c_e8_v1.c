// exp3: corrected conventions from FA dumps
//  - GCP g9: CPGetContact extern __stdcall (FA callee ret 0x4, no cleanup)
//  - SN sv6: fastcall short param (mangle YIPADF@Z = char* (short))
//  - PR p4:  mangle YAGFG@Z = unsigned short (short, unsigned short)
//  - UA u6/u7: init-order + inner-cmp spellings; u8: merged if(--count)
//  - HUD h5/h6/h7: value-in-ECX spellings (named e local; if/else-arms;
//    ternary-chain on the global)
typedef struct { unsigned char pad[8]; } D26u;

/* ---- HUD h5: e local, += on global, clamps written as if/else on global ---- */
extern int w26_hudBright; /* map _w26_hudBright=?hudBrightness@@3JA */

void __fastcall w26c_HUD_h5(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright = w26_hudBright + e;
    if (w26_hudBright < -0x100)
        return;
    if (w26_hudBright > 0x100)
        w26_hudBright = 0x100;
}

/* h6: if/else with per-branch stores incl. pass-through re-store */
void __fastcall w26c_HUD_h6(unsigned char p1)
{
    int e, n;
    e = (p1 < 1) ? -16 : 16;
    n = w26_hudBright + e;
    if (n < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    w26_hudBright = n;
    if (n > 0x100)
        w26_hudBright = 0x100;
}

/* h7: ternary chain on the global, value in else arms */
void __fastcall w26c_HUD_h7(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright += e;
    w26_hudBright = (w26_hudBright < -0x100) ? 0xffffff00 : w26_hudBright;
    w26_hudBright = (w26_hudBright > 0x100) ? 0x100 : w26_hudBright;
}

/* ---- GCP: CPGetContact __stdcall ---- */
extern int w26_numContactsQ; /* map _w26_numContactsQ=?numContacts@@3JA */
extern void *w26_objPtrsQ[]; /* map _w26_objPtrsQ=_objPtrs */
extern short __stdcall CPGetContactQ(long n); /* map _CPGetContactQ@4=?CPGetContact@@YGGJ@Z */
extern int __stdcall GRTo2dQ(unsigned int id, void *dst); /* map _GRTo2dQ@8=_GRTo2d@8 */

void __fastcall w26c_GCP_g9(unsigned int *o)
{
    int i;
    short c;
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

/* g10: g9 with unsigned short c */
void __fastcall w26c_GCP_g10(unsigned int *o)
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

/* ---- UA u6: init order max, count, best, walker ---- */
extern unsigned char w26_rankStr[]; /* map _w26_rankStr=_pilotRanks+0x1ec */
extern unsigned char w26_campArr[]; /* map _w26_campArr=_campaignPilot+0xdb0 */
extern int __cdecl strnicmpQ(const void *s1, const void *s2, unsigned int n); /* map _strnicmpQ=_strnicmp */
extern void *__cdecl memset(void *d, int c, unsigned int n); /* intrinsic - no map */

void w26c_UA_u6(void)
{
    unsigned char *walker;
    int count;
    unsigned long best;
    int max;
    do {
        max = 0;
        count = 0;
        best = 0;
        walker = (unsigned char *)w26_campArr;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    int r;
                    r = *(short *)(walker + 0x2e);
                    if (max <= r) {
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

/* u7: u6 with if (max < r) */
void w26c_UA_u7(void)
{
    unsigned char *walker;
    int count;
    unsigned long best;
    int max;
    do {
        max = 0;
        count = 0;
        best = 0;
        walker = (unsigned char *)w26_campArr;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    int r;
                    r = *(short *)(walker + 0x2e);
                    if (max < r) {
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

/* u8: u6 with ! (max > r) */
void w26c_UA_u8(void)
{
    unsigned char *walker;
    int count;
    unsigned long best;
    int max;
    do {
        max = 0;
        count = 0;
        best = 0;
        walker = (unsigned char *)w26_campArr;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    int r;
                    r = *(short *)(walker + 0x2e);
                    if (!(max > r)) {
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

/* ---- SN sv6: fastcall short param ---- */
extern unsigned char w26_soundOn; /* map _w26_soundOn=_soundOn */
extern unsigned char w26_sndDefA[]; /* map _w26_sndDefA=$FA$_d_4e7000+0x548 */
extern unsigned char w26_MODpA[]; /* map _w26_MODpA=?MOD@@3PAUMODSPEC@@A */
extern unsigned char w26_specialsA[]; /* map _w26_specialsA=_specials+0xb30 */

char *w26c_SN_sv6(short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    if (p1 < (short)16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}

/* sv7: __fastcall + unsigned p1 (< unsigned 16 compare) */
char *w26c_SN_sv7(unsigned short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDefA;
    if (p1 < 16)
        return (char *)&w26_MODpA[p1 * 84];
    return (char *)&w26_specialsA[p1 * 84];
}

/* ---- PR p4: mangle-correct types ---- */
extern void *w26_rudderArr[]; /* map _w26_rudderArr=_rudder */
extern void __fastcall NormalizeStickQ(unsigned int a, unsigned int b,
                                       unsigned int *c1, void *c2); /* map @NormalizeStickQ@16=@NormalizeStick@16 */

unsigned short w26c_PR_p4(short p1, unsigned short p2)
{
    int c = p1;
    unsigned short r;
    switch (c) {
    case 2:
        NormalizeStickQ(0, 0, 0, (void *)w26_rudderArr);
        return 0;
    case 3:
        return p2;
    default:
        return 0;
    }
}