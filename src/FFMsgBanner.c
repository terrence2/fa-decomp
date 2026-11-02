/* FFMsgBanner - FA rva 0xdc200 (901632) - EXACT probe verdict, tier1_a_r4.json entry 'FFMsgBanner_v3'
 * Form: patch-hybrid
 * Levers: nested-if CSE spelling + 83 3d reload patch with dir32 re-add
 * Maps: _aexit_rtn=__aexit_rtn+0x4 (linker DIR32 addend: content dword IS
 *   the disp — C accesses run at displacement 0, the +4/+8 disps come from
 *   the baked addend and the payload imm (04 00 00 00) at site 2)
 * patch 0xe: 8->7 B 83 3d 04000000 01, DIR32 re-add _aexit_rtn
 * patch 0xd: -> 2e
 * patch 0x9: -> 0d
 * Probes: v1-v3
 */
extern void *aexit_rtn[];
extern void (__cdecl *_adbgmsg)(void);
extern void __cdecl _NMSG_WRITE(int errnum);

void _FF_MSGBANNER(void)
{
    if (*(int *)aexit_rtn != 1) {
        if (*(int *)aexit_rtn != 0
            || *(int *)((char *)aexit_rtn + 8) != 1)
            return;
    }
    _NMSG_WRITE(0xfc);
    if (_adbgmsg)
        _adbgmsg();
    _NMSG_WRITE(0xff);
}
