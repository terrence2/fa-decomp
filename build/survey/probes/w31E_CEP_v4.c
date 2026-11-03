// _CallEventProc@8 @ rva 0x62b80 = 404352, 96 B. v4: like v3 but ev declared
// first (ev-first decl order).
typedef unsigned char (__cdecl *FPFL)(unsigned long *, unsigned long *,
                                     unsigned char *);
extern FPFL eventFilterProc;
extern unsigned char __cdecl CallUtilProc(int, unsigned int, unsigned long);

unsigned char __stdcall CallEventProcQ(unsigned long p1, unsigned long p2)
{
    unsigned char ev[4];
    FPFL fp;
    fp = eventFilterProc;
    if (fp != 0 && (*fp)(&p1, &p2, ev + 3))
        return ev[3];
    return CallUtilProc(3, p1 & 0xffff, p2);
}