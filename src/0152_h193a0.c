/* 0x193a0 (48 B) - unnamed frameless cdecl 5 args forwarding to
   jcopy_sample_rows(*a2, a3, a4, 0, a5, *(long *)(a1+0x52)); pushes
   right-to-left: *(a1+0x52), a5, 0, a4, a3, *a2. */
extern void __cdecl w43c_jcopyq(unsigned char **s, int w, unsigned char **d,
    int n, int h, unsigned long v);  /* ?jcopy_sample_rows@@YAXPAPAEH0HHI@Z */
void w43c_1930q(char *a1, unsigned char **a2, int a3, int a4, int a5)
{
    w43c_jcopyq((unsigned char **)*a2, a3, (unsigned char **)a4, 0, a5,
                *(unsigned long *)(a1 + 0x52));
}
