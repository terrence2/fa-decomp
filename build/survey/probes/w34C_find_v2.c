/* v2: first check is on the HANDLE PARAM itself (FA: mov edi,[esp+0x10];
 * test edi,edi) — v1 wrongly deref'd.  FA: p1->edi, p2->esi; 3 pushes at
 * prolog. */
typedef unsigned char (__stdcall *PFN)(void *find, void *data);
extern PFN _imp__FindNextFileA;
/* IAT slot; idata defines __imp__FindNextFileA (no @8) */

unsigned char __stdcall G_FindNextFileW(void *hfind, void *d)
{
    PFN cb;
    char *s;
    char c;

    if (hfind == 0)
        return 0;
    if (d == 0)
        return 0;
    cb = _imp__FindNextFileA;
    if (!cb(hfind, d))
        return 0;
    while (*(unsigned long *)d & 0x10) {
        if (cb(hfind, d) != 1)
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