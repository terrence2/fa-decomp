// n1 AmsgExit: banner gate (cmp [__aexit_rtn+4],1 mem-compare), NMSG_WRITE,
// exit through the __aexit_rtn fn-pointer dword (ff 15 mem-indirect call).
extern int msgFlag;
extern void __cdecl _FF_MSGBANNER(void);
extern void __cdecl _NMSG_WRITE(int errnum);
extern void (__cdecl *aexit_rtn)(int errnum);

void __cdecl _amsg_exit_q(int errnum)
{
    if (msgFlag == 1)
        _FF_MSGBANNER();
    _NMSG_WRITE(errnum);
    aexit_rtn(0xff);
}
