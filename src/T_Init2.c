// _T_Init2@0 @ rva 0xc2310 (64 B) — FA asm (FPO frame): 56 (push esi)/
//   be <_ambientInitProcs> (mov esi,tbl)/56?? loop: 8b 06 (mov eax,[esi])/
//   85 c0 test/j74.. e8 call fn/46 (inc esi)/81 fe <+0x44> (cmp esi,
//   _ambientInitProcs+0x44 — loop bound is an ADDRESS with reloc addend)/
//   jb ../ e8 _T_InitCloudProc / e8 _T_InitHorizonProc@0 / hidden store
//   c7 05 <_globalAmbientProc> <?T_CloudProc@@YAXJ@Z> (mov dword
//   [globalAmbientProc],T_CloudProc)/ e9 @T_SortTmapList@0 (fastcall
//   last-call tail jmp).  Runs the 0x11-entry ambientInitProcs fn table,
//   then the cloud/horizon inits, then installs T_CloudProc as the global
//   ambient proc and sorts the tmap list.  Plain C exact (probe
//   build/w4probe/b20b_ti2_v1.obj — exact).
typedef void (*INITFN)(void);
extern INITFN ambientInitProcs[];   /* _ambientInitProcs, 0x11 fns */
extern void (*globalAmbientProc)(long);   /* _globalAmbientProc */
extern void T_InitCloudProc(void);        /* decompiled, _T_InitCloudProc */
extern void __stdcall T_InitHorizonProc(void);
extern void __fastcall T_SortTmapList(void);
extern void __cdecl T_CloudProc(long);    /* ?T_CloudProc@@YAXJ@Z */

void __stdcall T_Init2(void)
{
    INITFN *p;
    for (p = ambientInitProcs; p < ambientInitProcs + 0x11; p++)
        if (*p)
            (*p)();
    T_InitCloudProc();
    T_InitHorizonProc();
    globalAmbientProc = T_CloudProc;
    T_SortTmapList();
}