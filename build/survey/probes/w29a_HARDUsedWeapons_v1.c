// 0x53330 _HARDUsedWeapons@12 (64 B) — v1
// stdcall, 3 dword args. HARDPtrs(arg1, &x, &y) fills a struct pointer;
// the +4 member is a signed short compared against arg3. Return char
// 0/1 via setl cl / mov al,cl.
struct W29HWP { char pad[4]; short f4; };
extern long __stdcall w29a_HPtrs(long a, struct W29HWP **r1, struct W29HWP **r2);
                                                  /* $FA$_t_451d90 _HARDPtrs@12 */

char __stdcall w29a_HUW(long i, long b, long c)
{
    struct W29HWP *x, *y;
    w29a_HPtrs(i, &x, &y);
    return x->f4 < c;
}