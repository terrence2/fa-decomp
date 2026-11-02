// 0x78c10 _LibFileSize (96 B) — v1
extern long __cdecl SearchLib27(char *name);
extern char *__fastcall MMLockq(char *h, long f);
extern void __fastcall MMUnlockq(char *h);
extern char *hintHndl27;

long __cdecl LibFileSize27(char *name)
{
    char *e;
    long idx;
    long size;

    idx = SearchLib27(name);
    if (idx == -1)
        return -1;
    e = (char *)MMLockq(hintHndl27, 0) + (idx * 8 - idx) * 5;
    size = -1;
    if (*(char *)e == 0)
        size = *(long *)(e + 0x1f);
    MMUnlockq(hintHndl27);
    return size;
}