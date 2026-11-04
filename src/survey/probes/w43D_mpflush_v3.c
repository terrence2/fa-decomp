/* 0x6afa0 ?MPFlushAll@@YIXD@Z 0x70 — v3: bit computed BEFORE the do-while
 * (forced callee-saved esi), MP_Info INSIDE the do-while so the back-edge
 * je retargets the MP_Info call; no pre-test so the for's own test emits
 * cmp eax,ebx / 7e jle; bottom jg via signed i.
 */
extern long numComputers;
extern long thisComputer;
extern char (__cdecl * w43D_mpfn)(long, char);
extern void * __cdecl MP_Info(void);
extern char __stdcall MPReceive(void);

void __fastcall w43D_mpflush(char n)
{
    long i, bit;
    void *info;
    for (i = 0; numComputers > i; i++) {
        if (thisComputer == i)
            continue;
        if ((*w43D_mpfn)(i, n))
            continue;
        bit = 1L << (i & 0xff);
        do {
            info = MP_Info();
            if ((*(unsigned long *)((char *)info + 0x158) & bit) == 0)
                break;
            MPReceive();
        } while ((*w43D_mpfn)(i, n) == 0);
    }
    return;
}