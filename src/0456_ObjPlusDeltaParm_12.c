/* w29g @ObjPlusDeltaParm@12 @ 0x62da0 — v1: struct-return spelling,
 * labs() intrinsic for the cdq/xor/sub abs chain */
extern long __cdecl labs(long v);

struct w29g_pk { unsigned char a, b, c, n; };

struct w29g_pk __fastcall w29g_opdp(int x, int y, int z)
{
    struct w29g_pk r;
    r.n = 0;
    while (labs(x) >= 0x80 || labs(y) >= 0x80 || labs(z) >= 0x80) {
        x >>= 1;
        y >>= 1;
        z >>= 1;
        r.n++;
    }
    r.a = (unsigned char)x;
    r.b = (unsigned char)y;
    r.c = (unsigned char)z;
    return r;
}