// _GVProc @ rva 0x72d00 (48 B: 40 code + 2×lea esp,[esp+0] pad) — the GV
// object class message dispatcher (cases 3/5 only), same uchar-param plan
// and _OBJProc cdecl forward as _CATGUYProc/_EJECTProc. Targets identity
// (_GVEventProc / _NPCWeaponsProc chunk names), probe w16b_2 exact.
extern long __cdecl OBJProc(unsigned char m);
extern long GVEventProc(unsigned long a, long b);
extern long NPCWeaponsProc(unsigned long a, long b);

long GVProc(unsigned char c)
{
    switch (c) {
    case 3:
        return (long)GVEventProc;
    case 5:
        return (long)NPCWeaponsProc;
    }
    return OBJProc(c);
}