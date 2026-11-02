// v3: no r variable — direct constant stores.
extern unsigned char w27a_v60b;
extern unsigned char w27a_mkB;
extern unsigned short w27a_mcs18w;
extern unsigned short w27a_press4c;
extern char w27a_mcsB[];
void __declspec(dllimport) __stdcall InitializeCriticalSectionQ(void *cs);
unsigned char __stdcall w27a_mi_q(void)
{
    if (w27a_v60b == 1)
        return 1;
    w27a_mcs18w = 0;
    w27a_mkB = 0;
    w27a_press4c = 0;
    InitializeCriticalSectionQ(&w27a_mcsB[0]);
    w27a_mkB = 1;
    return 1;
}
