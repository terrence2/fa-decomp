/* _MISSIONLoadCommonResources@0 @ 0x84350 (80B)
   walk: p = &missResA; v = *p; RMAccess(v,0x10c); p += 4 (FA sched: add esi,4
   after the two pushes, before the call); while (*p != 0). second list =
   missResB, arg2 = 0. */
extern void *missResA;   /* _pilotRanks+0x18 */
extern void *missResB;   /* _pilotRanks+0x158 */
extern void __stdcall RMAccess(unsigned long a, unsigned long b);

int __fastcall MISSIONLoadCommonResources_q(void)
{
    unsigned long *p;
    unsigned long v;
    if (missResA != 0) {
        p = (unsigned long *)&missResA;
        do {
            v = *p;
            RMAccess(v, 0x10c);
            p += 4;
        } while (*p != 0);
    }
    if (missResB != 0) {
        p = (unsigned long *)&missResB;
        do {
            v = *p;
            RMAccess(v, 0);
            p += 4;
        } while (*p != 0);
    }
    return 0;
}
