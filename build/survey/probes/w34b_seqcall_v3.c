/* rva 0x45e70 (_SEQcall), 64 B - v3: keep id in a plain unsigned long,
   compute SMAddress result through the unsigned long r, single exit path
   (r==0 falls through to the shared return). */
typedef int (cdecl *seqfn)(void *, unsigned long, unsigned long,
                           unsigned long, unsigned long, unsigned long,
                           unsigned long);

extern unsigned long __stdcall SMAddress(void *);

unsigned long sqfn;

int __cdecl SEQcall3(void *id, unsigned long p2, unsigned long p3,
                     unsigned long p4, unsigned long p5,
                     unsigned long p6, unsigned long p7, unsigned long p8)
{
    unsigned long r = SMAddress(id);
    if (r != 0)
        return ((seqfn)r)(id, p2, p3, p4, p5, p6, p7);
    return 0;
}