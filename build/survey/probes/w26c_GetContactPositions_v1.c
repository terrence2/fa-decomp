// @GetContactPositions@4 @ rva 0x14240 = 82496, 96 B (fastcall 1 arg ->
// ecx; loads numContacts, loops i<numContacts; CPGetContact cdecl ushort
// ret; ushort local kept in ax (test ax,ax), zero-extend via and for the
// objPtrs[c] index (wave-25 tell), GRTo2d@8 stdcall 2 args).
extern int w26_numContactsQ; /* map _w26_numContactsQ=?numContacts@@3JA */
extern void *w26_objPtrsQ[]; /* map _w26_objPtrsQ=_objPtrs */
extern unsigned short __cdecl CPGetContactQ(int n); /* map _CPGetContactQ=?CPGetContact@@YGGJ@Z */
extern int __stdcall GRTo2dQ(unsigned int id, void *dst); /* map _GRTo2dQ@8=_GRTo2d@8 */

void __fastcall w26c_GetContactPositions_q(unsigned int *o)
{
    int i;
    unsigned short c = 0;
    for (i = 0; i < w26_numContactsQ; i++) {
        c = CPGetContactQ(i);
        if (c == 0) {
            *(unsigned short *)&o[i] = 0x8000;
            continue;
        }
        {
            unsigned int *pd = &o[i];
            if (GRTo2dQ((unsigned int)w26_objPtrsQ[c] + 0x11, pd))
                *(unsigned short *)pd = 0x8000;
        }
    }
}