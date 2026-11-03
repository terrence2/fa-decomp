/* w33B_24bb2_v2.c -- same source as c1; CL reg-color patched to FA's (setle cl) */
extern long __stdcall w33b_apn(int a, int b, long *out, int c, int d);

char __fastcall w33b_24bb2(int a, int b)
{
    long x;

    w33b_apn(a, b, &x, 0, 1);
    return (char)(x <= 0x271000);
}