/* _G_FindNextFile@8 @ rva 0x78d70 (494960, 128 B) — stdcall unsigned char
 * (void **find, void *d): null-check both; imp-slot cached once (mov ebx,
 * __imp__FindNextFileA); call cb(*find, d); if ! => ret 0; while (d->attrs
 * & 0x10) { if (cb(*find, d) != 1) return 0; } lowercase->upper the name at
 * (char*)d+0x2c; return 1. */
typedef unsigned char (__stdcall *PFN)(void *find, void *data);
extern PFN _imp__FindNextFileA;
/* IAT slot; identity: idata defines __imp__FindNextFileA (no @8) */

unsigned char __stdcall G_FindNextFileW(void *hfind, void *d)
{
    void **find;
    PFN cb;
    char *s;
    char c;

    find = hfind;
    if (*find == 0)
        return 0;
    if (d == 0)
        return 0;
    cb = _imp__FindNextFileA;
    if (!cb(*find, d))
        return 0;
    while (*(unsigned long *)d & 0x10) {
        if (cb(*find, d) != 1)
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