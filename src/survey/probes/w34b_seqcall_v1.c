/* rva 0x45e70 (_SEQcall), 64 B - fn = SMAddress(id); if nonzero call
   fn(id, p2..p7) (7 args, rightmost first); return its value or 0. */
typedef int (cdecl *seqfn)(void *, unsigned long, unsigned long,
                           unsigned long, unsigned long, unsigned long,
                           unsigned long);

extern unsigned long __stdcall SMAddress(void *);

int __cdecl SEQcall(void *id, unsigned long p2, unsigned long p3,
                    unsigned long p4, unsigned long p5,
                    unsigned long p6, unsigned long p7, unsigned long p8)
{
    seqfn fn;
    fn = (seqfn)SMAddress(id);
    if (fn == 0)
        return 0;
    return fn(id, p2, p3, p4, p5, p6, p7);
}