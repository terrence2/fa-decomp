/* FA 0x6efd0 v2: currentTime as SCALAR unsigned short (moffs 66 a1 form);
 * call args fixed to FA's order: msg(-1, buf, 5, 1) — FA pushes 1,5,buf,-1
 * (arg4..arg1 right-to-left: arg1=-1 sits at TOS, arg2=buf, arg3=5, arg4=1). */
extern long numComputers;
extern unsigned long endScenarioSetTime;
extern unsigned short currentTime;
extern void __stdcall w45E_msg4(char *buf, long a2, long a3, long a4);

void w45E_6efd0_v2(void)
{
    char buf[8];
    long v;

    if (numComputers == 1)
        return;
    buf[0] = 'L';
    v = endScenarioSetTime - currentTime;
    *(long *)(buf + 1) = v;
    if (v < 0)
        *(long *)(buf + 1) = 0;
    w45E_msg4(-1, buf, 5, 1);
}
