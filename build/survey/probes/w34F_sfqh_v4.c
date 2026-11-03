extern int timerTicks;
extern void *w34f_qhcb;
extern void *w34f_qhs;
extern void *w34f_qhp;

void __cdecl w34f_sfqh(void)
{
    if (*(int *)w34f_qhcb <= timerTicks) {
        (*(void (__cdecl **)(int, int, int))((char *)(*(void **)w34f_qhp) + 0x4e))((int)w34f_qhs, 0, 0);
        w34f_qhcb = (void *)((*(int *)((char *)(*(void **)w34f_qhp) + 6) << 8) + (int)timerTicks);
    }
}
