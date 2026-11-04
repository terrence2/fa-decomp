/* w44C ac9c0 (96 B) — unnamed: class-entity state poke + vtable call, then a
 * flag-gated clamp + call to stub chunk 0xac790 ($FA$_t_4ac790) with self.
 * FA re-loads *(long*)p three times (its own CSE behavior); word at +0xe
 * tested against 0xcf/0xcc first (mov esi,[esp+8]; mov eax,[esi+0xe]). */
extern void __cdecl w44c_f4ac790(void *);       /* $FA$_t_4ac790 */

void w44c_ac770(long *p, long arg2)
{
    long o, v, c, e;
    e = *(long *)((char *)p + 0xe);
    if (e != 0xcf && e != 0xcc) {
        o = *(long **)p;                                    /* 1st [esi] */
        *(long *)((char *)o + 0x14) = 0x12;
        o = *(long **)p;                                    /* 2nd [esi] */
        *(long *)((char *)o + 0x18) = *(long *)((char *)p + 0xe);
        o = *(long **)p;                                    /* 3rd [esi] */
        (*(void (__cdecl **)(long *))o)((void *)p);
    }
    c = arg2;
    if (c <= 0)
        c = 1;
    e = *(long *)((char *)p + 0x17e);
    if (*(char *)(e + 0x11) != 0) {
        v = *(long *)((char *)p + 0x72);
        if (c > v)
            c = v;
    }
    *(long *)((char *)p + 0x7a) = c;
    w44c_f4ac790((void *)p);
}