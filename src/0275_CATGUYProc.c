// _CATGUYProc @ rva 0x41d40 (48 B, all code — no tail pad) — the CATGUY
// object class message dispatcher: switch on the (zero-extended) message
// id, return the per-class handler address for 2/3, NULL for 5, else
// forward to _OBJProc cdecl (push eax — FA passes only the al byte, the
// upper 24 bits of eax are stale caller junk; uchar param reproduces the
// whole plan: xor ecx,ecx / mov al,[esp+4] / mov cl,al / 32-bit cmp chain /
// push eax). Plain C switch, probe w16b_1 exact byte-for-byte.
extern long __cdecl OBJProc(unsigned char m);
extern long CATGUYMoveProc(unsigned long a, long b);
extern long CATGUYEventProc(unsigned long a, long b);

long CATGUYProc(unsigned char c)
{
    switch (c) {
    case 2:
        return (long)CATGUYMoveProc;
    case 3:
        return (long)CATGUYEventProc;
    case 5:
        return 0;
    }
    return OBJProc(c);
}