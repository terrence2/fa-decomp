/* w33B_24bb2_c1.c -- 36-B fastcall wrapper at 0x24bb2: APNearest then range test */
extern long __stdcall w33b_apn(int a, int b, long *out, int c, int d);

char __fastcall w33b_24bb2(int a, int b)
{
    long x;

    w33b_apn(a, b, &x, 0, 1);
    return (char)(x <= 0x271000);
}