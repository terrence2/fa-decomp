/* w34A @ rva 0xd9020 (dec 888864), 33 B, FPO fpo/esp, unnamed ($FA$_t_4d9020).
 * FA bytes: mov edx,[esp+8](t)/push esi/mov ecx,[esp+8](a)/
 * eax = t[0]; eax += a; esi = t[1]; test esi; jl epilog/
 * ecx = a[n]; edx = t[2]; eax += *(long*)(a[n]+t[2]); eax += n/
 * pop esi/ret (cdecl).
 */
long w34A_d9020(long *a, long *t)
{
    long r, n;

    r = t[0];
    r += (long)a;
    n = t[1];
    if (n >= 0) {
        r += *(long *)((char *)a[n] + t[2]);
        r += n;
    }
    return r;
}