/* rva 450368 (0x6df40) v2 — v1 was byte-exact except: (a) m[0x5e]]
 * typo (FA word at +0x158 = m[0x56]), (b) latch encoding FA
 * 3b d8 7c d9 (cmp ebx,eax; jl) vs CL 3b c3 7f d9 — 4-B patch. */
extern volatile long w40E_nComp;
extern long w40E_mps[];
extern void *w40E_MP_Info(void);

void __cdecl w40E_ClrMps(void)
{
    long *m;
    long i;
    long d;

    m = 0;
    i = 0;
    if (w40E_nComp > 0) {
        d = 0;
        do {
            m = w40E_MP_Info();
            if (!(m[0x56] & (1 << (i & 0xff))))
                w40E_mps[i] = d;
            i++;
        } while (i < w40E_nComp);
    }
}