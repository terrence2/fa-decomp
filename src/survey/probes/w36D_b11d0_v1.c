/* w36D_b11d0_v1: (t, v) setter+cdecl-vfn stub @ 0xb11d0 (48 B).
   FA: edx=[esp+4] (t) / push ebx / eax=[edx] / ebx=[esp+0xc] (v) /
   push edx / c7 40 14 imm 35 (p[5]) / ecx=[edx] (reload) / [ecx+0x18]=ebx /
   eax=[edx] (reload) / call [eax] (cdecl 1-arg, arg=t) / add esp,4 pop ebx ret.
   Triple reload of *(t): spelling via three separate deref statements
   (CL won't CSE across [t]-targeted stores/pointers... probe). */
typedef unsigned long UL;
typedef void (__cdecl *PFN)(UL);

void w36d_b11d0(UL t, UL v)
{
    *(UL *)(*(UL *)t + 0x14) = 0x35;
    *(UL *)(*(UL *)t + 0x18) = v;
    (*(PFN *)(*(UL *)t))(t);
}