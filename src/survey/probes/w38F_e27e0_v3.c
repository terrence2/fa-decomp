/* w38F_e27e0_v3: unnamed @ rva 0xe27e0 — CRT argv-block init: malloc(0x80),
 * store/reload via fake globals mapped to __acmdln+8 / +4. v3: non-volatile
 * locals — FA tests the malloc eax directly after the store (no volatile
 * reload); the later reads reload from the mapped globals. */
extern void *__cdecl _malloc(unsigned long);
extern void __cdecl _amsg_exit(int);
extern void *w38e_h;
extern void *w38e_l;

void _w38e_x(void)
{
    void *q;
    w38e_h = q = _malloc(0x80);
    if (q == 0)
        _amsg_exit(0x18);
    *(void **)w38e_h = 0;
    w38e_l = w38e_h;
}