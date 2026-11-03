// 0xd4a60 (16 B, unnamed) — v1: moffs load of old value + store of param,
// returns the OLD value (a1 read is the return)
extern void *w32a_ldv;               /* -> __ldused+0x4 */

long __cdecl w32a_ldvset(void *p)
{
    long o = (long)w32a_ldv;
    w32a_ldv = p;
    return o;
}