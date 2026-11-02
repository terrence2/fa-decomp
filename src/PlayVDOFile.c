// 0xab2c0 ?PlayVDOFile@@YAFPADFD@Z (48 B) — v2 (!= shape: inline ret-6 right
// after the test, je skips to the call path, eax holds the zero-extended n)
extern short __cdecl PlayVDOString27(void *a, short n, void *c, void *d,
                                     void *e, void *f, char g);

short __cdecl PlayVDOFile27(void *a, short v, char c)
{
    short n;

    n = v;
    if (n != 0x3e8)
        return 6;
    return PlayVDOString27(a, n, 0, 0, 0, 0, c);
}
