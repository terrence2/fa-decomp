/* v3: FA derefs the handle pointer at each call (push esi; mov eax,[edi];
 * push eax = cb(*ph, d)) and re-tests the deref inside the while loop;
 * first check tests p1 itself. */
typedef unsigned char (__stdcall *PFN)(void *find, void *data);
extern PFN _imp__FindNextFileA;
/* IAT slot; idata defines __imp__FindNextFileA@8 — map added in config */

unsigned char __stdcall G_FindNextFileW(void **phfind, void *d)
{
    PFN cb;
    char *s;
    char c;

    if (phfind == 0)
        return 0;
    if (d == 0)
        return 0;
    cb = _imp__FindNextFileA;
    if (!cb(*phfind, d))
        return 0;
    while (*(unsigned long *)d & 0x10) {
        if (cb(*phfind, d) != 1)
            return 0;
    }
    s = (char *)d;
    c = s[0x2c];
    s += 0x2c;
    if (c) {
        do {
            c = *s;
            if (c >= 0x61 && c <= 0x7a)
                c -= 0x20;
            *s = c;
            c = s[1];
            s++;
        } while (c != 0);
    }
    return 1;
}