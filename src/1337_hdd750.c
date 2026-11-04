/* w44C dd750 (102 B) — unnamed: 7-field free sweep. Guard: p == 0 or
 * p->f0c == (long)(&__no_lead_zeros + 8) (address-literal compare, b8-class
 * via extern-array pointer arithmetic). FA loads each field into eax then
 * pushes (release pattern). */
extern void __cdecl free(void *);               /* _free */
extern char w44c_d8nz[];                        /* __no_lead_zeros */

void w44c_ddf0(void *sp)
{
    long o, v;
    o = (long)sp;
    if (o == 0)
        return;
    v = *(long *)((char *)o + 0xc);
    if (v == (long)(w44c_d8nz + 8))
        return;
    free((void *)v);
    free((void *)*(long *)((char *)o + 0x10));
    free((void *)*(long *)((char *)o + 0x14));
    free((void *)*(long *)((char *)o + 0x18));
    free((void *)*(long *)((char *)o + 0x1c));
    free((void *)*(long *)((char *)o + 0x20));
    free((void *)*(long *)((char *)o + 0x24));
}