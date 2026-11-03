/* rva 0x7c260 (32 B): fa_c280(&a1, a2) -> discards, then atoi(a1).
 * FA: lea ecx,[esp+4] (address OF stack a1), edx=[esp+8], call $FA$
 * _t_47c280; mov eax,[esp+4]; push/call _atoi (cdecl); add esp,4;
 * ret 0x8 (f cleans 8 B = stdcall 2 args). Frameless, no prolog. */
extern int w33h_c280(char **a, char *b);    /* $FA$_t_47c280, fastcall */
extern int atoi(const char *);

int __stdcall w33h_7c260(char *a1, char *a2)
{
    w33h_c280(&a1, a2);
    return atoi(a1);
}
