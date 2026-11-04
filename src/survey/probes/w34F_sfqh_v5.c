extern int timerTicks;
extern int w34f_qhcb;
extern void *w34f_qhs;
extern void *w34f_qhp;

void __cdecl w34f_sfqh(void)
{
    if (w34f_qhcb <= timerTicks) {
        (*(void (__cdecl **)(int, int, int))((char *)w34f_qhp + 0x4e))((int)w34f_qhs, 0, 0);
        w34f_qhcb = ((*(int *)((char *)w34f_qhp + 6) << 8) + timerTicks);
    }
}
