/* w36D_630f0_v1: stdcall(2) vtable-dispatch stub @ 0x630f0 (48 B).
   FA: push ebx / xor eax,eax / mov bl,[esp+0xc] / push esi /
   mov esi,[esp+0xc] / ecx=[esi+0x6c] test je / push ebx call ecx
   (cdecl 1-arg) / add esp,4 / test eax jne / push ebx, eax=[esi+5],
   call [eax+0x7d] / add esp,4 / pop esi ebx / ret 8. */
typedef unsigned long UL;
typedef int (__cdecl *PFN)(unsigned char);

int __stdcall w36d_630f0(void *p, unsigned char b)
{
    int r = 0;
    PFN f = *(PFN *)(((char *)p) + 0x6c);
    if (f) r = f(b);
    if (r) return r;
    return (*(PFN *)(((char *)*(UL **)(((char *)p) + 5)) + 0x7d))(b);
}