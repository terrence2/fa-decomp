/* chunk @ rva 0xdf2f0 (88 B) v6 -- /G4 flag variant of v3 */
typedef long (__stdcall *PFQ)(void *);

extern void __stdcall w35_term(void);            /* ?terminate@@YAXXZ */
extern int __cdecl w35_vexec(PFQ);               /* ?_ValidateExecute@@YAHP6GHXZ@Z */

PFQ __declspec(dllimport) __stdcall w35_pf(void *);   /* ff 15 route */
extern long w35_pfval;                           /* 83 3d cmp spelling */
extern long w35_pfv2;                            /* a1 moffs load spelling */

long __stdcall w35_cuef6(void *ep)
{
    long *er;
    er = *(long **)ep;
    if (er[0] == 0xe06d7363 && er[4] == 3 && er[5] == 0x19930520) {
        w35_term();
        return 1;
    }
    if (w35_pfval) {
        if (w35_vexec((PFQ)w35_pfv2))
            return w35_pf(ep);
    }
    return 0;
}