// exp3: corrected conventions from FA dumps
//  - GCP g9: CPGetContact extern __stdcall (FA callee ret 0x4, no cleanup)
//  - SN sv6: fastcall short param (mangle YIPADF@Z = char* (short))
//  - PR p4:  mangle YAGFG@Z = unsigned short (short, unsigned short)
//  - UA u6/u7: init-order + inner-cmp spellings; u8: merged if(--count)
//  - HUD h5/h6/h7: value-in-ECX spellings (named e local; if/else-arms;
//    ternary-chain on the global)
typedef struct { unsigned char pad[8]; } D26u;

/* h7: ternary chain on the global, value in else arms */
void __fastcall w26c_HUD_h7(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright += e;
    w26_hudBright = (w26_hudBright < -0x100) ? 0xffffff00 : w26_hudBright;
    w26_hudBright = (w26_hudBright > 0x100) ? 0x100 : w26_hudBright;
}

/* ---- GCP g9: CPGetContact __stdcall ---- */
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

