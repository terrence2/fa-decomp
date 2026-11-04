// ?MPEveryoneStatus@@YIDJ@Z @ rva 0x70970 = 461168, 80 B.
extern long mpStatus[];        /* map _mpStatus=?mpStatus@@3PAJA */
extern long numComputers;
extern long *MP_InfoQ(void);   /* map _MP_InfoQ=?MP_Info@@YAPAUMP_INFO@@XZ */

typedef struct { unsigned char pad[0x158]; unsigned long bits; } ES_MPI;

char __fastcall MPEveryoneStatus(long st)
{
    int i;
    ES_MPI *p;
    for (i = 0; i < numComputers; i++) {
        p = (ES_MPI *)MP_InfoQ();
        if (p->bits & (1 << i)) {
            if (mpStatus[i] != st)
                return 0;
        }
    }
    return 1;
}