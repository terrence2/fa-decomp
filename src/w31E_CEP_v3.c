// _CallEventProc@8 @ rva 0x62b80 = 404352, 96 B. v3: params are PLAIN
// unsigned long values, the filter receives their ADDRESSES (&p1/&p2), and
// decl order fp-first (FA: mov ecx,[g]; test; 90; push ebx; je skip; lea
// eax/edx/ebx staging; push; push; push; call ecx; ...).
typedef unsigned char (__cdecl *FPFL)(unsigned long *, unsigned long *,
                                     unsigned char *);
extern FPFL eventFilterProc;
extern unsigned char __cdecl CallUtilProc(int, unsigned int, unsigned long);

unsigned char __stdcall CallEventProcQ(unsigned long p1, unsigned long p2)
{
    FPFL fp;
    unsigned char ev[4];
    fp = eventFilterProc;
    if (fp != 0 && (*fp)(&p1, &p2, ev + 3))
        return ev[3];
    return CallUtilProc(3, p1 & 0xffff, p2);
}