// 0xd90a0 __mtinit — v2: || shape forces shared ret0, re-read idx
__declspec(dllimport) unsigned long __stdcall TlsAlloc(void);
__declspec(dllimport) int __stdcall TlsSetValue(unsigned long idx, void *val);
__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
extern unsigned char w29fCtypes[];      /* -> __ctype (TLS idx at +0x3b0) */
extern void __cdecl w29fMtInitLocks(void);
extern void *__cdecl w29fCalloc(unsigned long n, unsigned long sz);
extern void __cdecl w29fInitPtd(void *ptd);

int __cdecl mtinitX_q(void)
{
    void *ptd;
    w29fMtInitLocks();
    *(long *)((char *)w29fCtypes + 0x3b0) = (long)TlsAlloc();
    if (*(long *)((char *)w29fCtypes + 0x3b0) == -1L)
        return 0;
    ptd = w29fCalloc(1, 0x74);
    if (ptd == 0 || !TlsSetValue((unsigned long)*(long *)((char *)w29fCtypes + 0x3b0), ptd))
        return 0;
    w29fInitPtd(ptd);
    *(long *)ptd = (long)GetCurrentThreadId();
    ((long *)ptd)[1] = -1;
    return 1;
}