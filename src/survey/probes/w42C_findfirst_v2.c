/* w42C cand1: _G_FindFirstFile@8 @0x78ce0 (144 B) — stdcall 2 params.
   v2: not-directory branch spelled as if(!(attr & 0x10)) so CL emits je. */
__declspec(dllimport) unsigned long __stdcall FindFirstFileA(char *spec, void *data);
__declspec(dllimport) unsigned char __stdcall FindNextFileA(unsigned long h, void *data);
__declspec(dllimport) void __stdcall FindClose(unsigned long h);
void *__cdecl w42c_malloc(long n);

long __stdcall G_FindFirstFile(char *name, void *data)
{
    long h;
    void **s;
    char *p, c;

    h = FindFirstFileA(name, data);
    if (h == -1)
        return 0;
    for (;;) {
        if (!(*(unsigned long *)data & 0x10)) {
            s = (void **)w42c_malloc(0x16);
            if (!s) {
                FindClose(h);
                return 0;
            }
            data = (char *)data + 0x2c;
            *(long *)s = h;
            *((char *)s + 4) = 0;
            p = (char *)data;
            if (*p == 0)
                return 0;
            c = *p;
            while (c != 0) {
                if (c >= 0x61 && c <= 0x7a) {
                    c -= 0x20;
                    *p = c;
                }
                p++;
                c = *p;
            }
            return (long)s;
        }
        if (FindNextFileA(h, data) == 1)
            continue;
        FindClose(h);
        return 0;
    }
}
