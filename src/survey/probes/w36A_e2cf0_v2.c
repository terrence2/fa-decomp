// w36A_e2cf0_v2: r=0 first-decl (v1 had t=v+m first, CL hoisted a
// redundant param load before the prolog push and emitted the loads in
// the wrong interleave; FA = push esi / xor eax,eax / mov edx,[esp+0xc]
// (m) / mov ecx,[esp+8] (v) / lea esi,[ecx+edx] / ...).

unsigned long __cdecl tAddCry(unsigned long v, unsigned long m, unsigned long *w)
{
    unsigned long r = 0;
    unsigned long t;

    t = v + m;
    if (v > t || m > t)
        r = 1;

    *w = t;
    return r;
}