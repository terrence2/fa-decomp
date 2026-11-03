/* v2: c280 is FASTCALL (FA: ecx=&a1, edx=a2) — v1 declared cdecl so CL
 * pushed both args.  &a1 = lea ecx,[esp+4] (address of the stack a1). */
extern int __fastcall w33h_c280(char **a, char *b);
extern int atoi(const char *);

int __stdcall w33h_7c260(char *a1, char *a2)
{
    w33h_c280(&a1, a2);
    return atoi(a1);
}
