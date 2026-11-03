// _CallEventProc@8 @ rva 0x62b80 = 404352, 96 B. v2: fn-ptr LOCAL so CL
// loads the pointer into a register and emits `call ecx` (FF D1), not
// `call ds:[global]` (FF 15). FA: mov ecx,[g]; test; 90; push ebx; je skip;
// ...; call ecx; ...
typedef unsigned char (__cdecl *FPFL)(unsigned long *, unsigned long *,
                                     unsigned char *);
extern FPFL eventFilterProc;  /* data pointer _eventFilterProc, identity */
extern unsigned char __cdecl CallUtilProc(int, unsigned int, unsigned long);

unsigned char __stdcall CallEventProcQ(unsigned long *p1, unsigned long *p2)
{
    unsigned char ev[4];
    FPFL fp;
    fp = eventFilterProc;
    if (fp != 0 && (*fp)(p1, p2, ev + 3))
        return ev[3];
    return CallUtilProc(3, *p1 & 0xffff, *p2);
}