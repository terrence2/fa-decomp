/* __FindFirst@8 (rva 0x78930, 192 B): first-pass find wrapper.
 *   - filenames inside the "Saudi Arabian" hint table (string baked at
 *     0x4f3fdc, i.e. ?hintHndl@@3PAUT_HANDLE@@A+0xb8) go straight through
 *     to _G_FindFirstFile@8;
 *   - everything else allocates the 0x16-B find state from the wave-28
 *     malloc wrapper (unnamed chunk rva 0xd4980) and, when that fails,
 *     frees/reports nothing via the tiny free wrapper (rva 0xd4880);
 *   - state init: [ebx+0]=0, byte [ebx+4]=1, dword [ebx+5]=0, arg1 copied
 *     to [ebx+9] with FA's inline strlen + rep-movsd/rep-movsb strcpy;
 *   - the state is filled from __FindNext@8(state, arg2) and on success
 *     the name at state+0x2c is upper-cased in place ('a'..'z' -> -0x20).
 */
extern char *strstr(const char *, const char *);
extern long __stdcall G_FindFirstFile(char *pat, long *fd);
extern char *FA_t_4d4980(unsigned long size);
extern void FA_t_4d4880(void *p);
extern char __stdcall FindNextX(char *state, long *fd);

char *__stdcall FindFirst(const char *pat, long *fd)
{
    char *state;
    char *p;
    if (strstr(pat, "Saudi Arabian"))
        return (char *)G_FindFirstFile((char *)pat, fd);
    state = FA_t_4d4980(0x16);
    if (!state)
        return 0;
    state[0] = 0;
    state[4] = 1;
    *(long *)(state + 5) = 0;
    for (p = state + 9; (*p++ = *pat++) != 0; )
        ;
    if (FindNextX(state, fd) != 1)
        return FA_t_4d4880(state), (char *)0;
    for (p = state + 0x2c; *p; p++)
        if (*p >= 'a' && *p <= 'z')
            *p -= 0x20;
    return state;
}