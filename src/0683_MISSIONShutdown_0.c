/* w37B 0x7ff10 (rva 524048, 128 B) _MISSIONShutdown@0 v1: stdcall(void).
 * FA: if (byte [_selectedTypeName+0x10]) { store 0 to it; WRShutdown
 * ... call train ..., mov ecx,_mainV; call $FA$_t_40e1c0 (fastcall 1-arg);
 * ...; if (_missionName[0]) { push _missionName; call _RMFree@4; }
 * push 1; call _RMFreeAllId@4; mov ecx,1; call @MMFreeAllId@4;
 * mmAllocId = 0; } ret.  No frame. */
extern void __stdcall WRShutdown(void);        /* _WRShutdown@0 */
extern void __stdcall T_Shutdown(void);        /* _T_Shutdown@0 */
extern void __stdcall T_ShutdownDatabase(void);/* _T_ShutdownDatabase@0 */
extern void __stdcall OBJShutdown(void);       /* _OBJShutdown@0 */
extern void __fastcall w37b_msinitX(void *v);  /* $FA$_t_40e1c0 */
extern void __stdcall HUDShutdown(void);       /* _HUDShutdown@0 */
extern void __stdcall CTShutdown(void);        /* _CTShutdown@0 */
extern void __stdcall MPMissionShutdown(void); /* _MPMissionShutdown@0=?MPMissionShutdown@@YGXXZ */
extern void __fastcall SoundAllOff(void);      /* @SoundAllOff@0=?SoundAllOff@@YIXXZ */
extern void __stdcall SAYShutdown(void);       /* _SAYShutdown@0 */
extern void __stdcall StreamersShutdown(void); /* _StreamersShutdown@0 */
extern void __stdcall RMFree(char *s);         /* _RMFree@4 */
extern void __stdcall RMFreeAllId(long id);    /* _RMFreeAllId@4 */
extern void __fastcall MMFreeAllId(long id);   /* @MMFreeAllId@4 */
extern char missionName[];                     /* _missionName */
extern char w37b_selX;                         /* _selectedTypeName+0x10 */
extern char mmAllocId;                         /* ?mmAllocId@@3EA */
extern char mainV[];                           /* _mainV */

void __stdcall MISSIONShutdown(void)
{
    if (w37b_selX) {
        w37b_selX = 0;
        WRShutdown();
        T_Shutdown();
        T_ShutdownDatabase();
        OBJShutdown();
        w37b_msinitX(mainV);
        HUDShutdown();
        CTShutdown();
        MPMissionShutdown();
        SoundAllOff();
        SAYShutdown();
        StreamersShutdown();
        if (missionName[0])
            RMFree(missionName);
        RMFreeAllId(1);
        MMFreeAllId(1);
        mmAllocId = 0;
    }
}