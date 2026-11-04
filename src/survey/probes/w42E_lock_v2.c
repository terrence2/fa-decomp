/* w42E candidate 4 v2: __lock — decl order flipped (lockptr declared first) */
extern void *__cdecl malloc(unsigned long);
extern void __cdecl free(void *);
extern void __cdecl _amsg_exit(int);
extern void __cdecl _unlock(int);
extern void *_locktable[];
__declspec(dllimport) void __stdcall InitializeCriticalSection(void *cs);
__declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);

void __cdecl _lock(int locknum)
{
    void *lockptr;
    void **p;

    if (*(p = (void **)&_locktable[locknum]) == 0) {
        if ((lockptr = malloc(0x18)) == 0)
            _amsg_exit(0x11);
        _lock(0x11);
        if (*p == 0) {
            InitializeCriticalSection(lockptr);
            *p = lockptr;
        } else
            free(lockptr);
        _unlock(0x11);
    }
    EnterCriticalSection(*p);
}