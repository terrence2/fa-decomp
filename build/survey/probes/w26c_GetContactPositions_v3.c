// @GetContactPositions@4 @ rva 0x14240 = 82496, 96 B — v3: decl order
//   pd, i (no c local; c transient in ax).
extern int w26_numContactsQ; /* map _w26_numContactsQ=?numContacts@@3JA */
extern void *w26_objPtrsQ[]; /* map _w26_objPtrsQ=_objPtrs */
extern unsigned short __cdecl CPGetContactQ(int n); /* map _CPGetContactQ=?CPGetContact@@YGGJ@Z */
extern int __stdcall GRTo2dQ(unsigned int id, void *dst); /* map _GRTo2dQ@8=_GRTo2d@8 */

void __fastcall w26c_GetContactPositions_q3(unsigned int *o)
{
    unsigned int *pd;
    int i;
    for (i = 0; i < w26_numContactsQ; i++) {
        if (CPGetContactQ(i) == 0) {
            *(unsigned short *)&o[i] = 0x8000;
            continue;
        }
        pd = &o[i];
        if (GRTo2dQ((unsigned int)w26_objPtrsQ[*(unsigned short *)&i] + 0x11, pd)) /* bogus keeps shape */
            *(unsigned short *)pd = 0x8000;
    }
}