// exp6: probe whether loop-bottom cmp orientation depends on TU context
typedef struct { unsigned char pad[2]; } D26A;

extern int w26_numContactsQ; /* map _w26_numContactsQ=?numContacts@@3JA */
extern void *w26_objPtrsQ[]; /* map _w26_objPtrsQ=_objPtrs */
extern short __stdcall CPGetContactQ(long n); /* map _CPGetContactQ@4=?CPGetContact@@YGGJ@Z */
extern int __stdcall GRTo2dQ(unsigned int id, void *dst); /* map _GRTo2dQ@8=_GRTo2d@8 */

void __fastcall w26c_GCP_t1(unsigned int *o)
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

/* dummy sibling (unrelated) to test TU-context sensitivity */
extern int w26_q2;

void w26c_GCP_dummy(void)
{
    w26_q2 = w26_q2 + 1;
}

/* t3: same body again after the dummy */
void __fastcall w26c_GCP_t3(unsigned int *o)
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