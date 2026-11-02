// __amsg_exit @ rva 0xd6230 (42 B) — runtime-error exit path CONVERTED
// (band N1, 2026-11-02). The flag dword at __aexit_rtn+0x4 (the "already
// showing a message" state, also read by __FF_MSGBANNER/__NMSG_WRITE) gates
// the banner. Old wall: CL folds cmp [mem],imm into an a1 moffs load +
// cmp reg (w13c probes); fix is the load-folds-to-test hybrid — plain C
// `if (msgFlag == 1) _FF_MSGBANNER(); _NMSG_WRITE(errnum); aexit_rtn(0xff);`
// + one 8->8 B patch: CL a1+3f?? head -> FA 83 3d msgFlag,1 (DIR32 re-add
// _msgFlag at site 2, payload dword zero). Everything else is natural: the
// `extern void (__cdecl *aexit_rtn)(int)` global fn-pointer extern makes CL
// emit ff 15 [mem] matching FA's indirect call (fnc_toCallDuringAnswer
// precedent), and aexit_rtn(0xff) gives the 68 ff 00 00 00 push. CL already
// cmp-mem-folded the call sequence, only the load form differs.
// Probes: w13c_amsg1/amsg2 naked asm; n1_AmsgExit_v1 EXACT.
extern int msgFlag;
extern void __cdecl _FF_MSGBANNER(void);
extern void __cdecl _NMSG_WRITE(int errnum);
extern void (__cdecl *aexit_rtn)(int errnum);

void __cdecl _amsg_exit(int errnum)
{
    if (msgFlag == 1)
        _FF_MSGBANNER();
    _NMSG_WRITE(errnum);
    aexit_rtn(0xff);
}