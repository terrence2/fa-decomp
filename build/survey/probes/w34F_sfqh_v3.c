typedef void (__cdecl *PF3)(int, int, int);
extern int timerTicks;
extern void *w34f_qhcb;
extern void *w34f_qhs;
extern void *w34f_qhp;

void __cdecl w34f_sfqh(void)
{
    void *p;
    PF3 *pp;
    if ((int)w34f_qhcb <= timerTicks) {
        p = w34f_qhp;
        pp = (PF3 *)((char *)p + 0x4e);
        (*pp)((int)w34f_qhs, 0, 0);
        w34f_qhcb = (void *)((*(int *)((char *)w34f_qhp + 6) << 8) + (int)timerTicks);
    }
}