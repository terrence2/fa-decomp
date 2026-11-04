/* RemapRelocate v9: no s copy — the param id is read directly and mutated
 * in place (matches FA's single si-flow). */
struct T_HANDLE;

extern unsigned long *__fastcall MMAccessW(struct T_HANDLE *);
extern void __cdecl w38e_radd(struct T_HANDLE *, long);
extern unsigned char curPalette[];
extern void *__cdecl memmove(void *, const void *, unsigned long);

void __cdecl RemapRelocate(struct T_HANDLE *h, short id)
{
    unsigned long *m;
    unsigned char *dst;
    unsigned long cnt;
    m = MMAccessW(h);
    dst = (unsigned char *)*(unsigned long **)((char *)m + 0x12);
    cnt = *(unsigned long *)((char *)m + 0x16) / 3U;
    if (id > 0x100) {
        id -= 0x100;
        cnt -= (unsigned long)id;
        dst += id * 3;
    } else {
        w38e_radd(h, id);
    }
    if ((long)cnt > 0)
        memmove(curPalette + id * 3, dst, cnt * 3);
}