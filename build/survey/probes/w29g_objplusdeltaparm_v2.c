/* w29g @ObjPlusDeltaParm@12 @ 0x62da0 — v2: xor-shift abs spelling */
struct w29g_pk2 { unsigned char a, b, c, n; };

#define ABSW(v) (((v) ^ ((v) >> 31)) - ((v) >> 31))

struct w29g_pk2 __fastcall w29g_opdp2(int x, int y, int z)
{
    struct w29g_pk2 r;
    r.n = 0;
    while (ABSW(x) >= 0x80 || ABSW(y) >= 0x80 || ABSW(z) >= 0x80) {
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