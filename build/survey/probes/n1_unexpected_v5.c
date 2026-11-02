// n1 unexpected v5: unexpected_v3 spelling (25 B: mov ecx,[eax+64]/test ecx
// loads-then-test) — the one-patch candidate: rewrite to FA's 83 78 64 00.
extern void *__cdecl _getptd(void);
extern void __cdecl termX(void);

typedef void (__cdecl *unh_t)(void);

void __cdecl unexpected_l(void)
{
    if (*(unsigned long *)((char *)_getptd() + 0x64))
        (*(unh_t *)((char *)_getptd() + 0x64))();
    termX();
}
