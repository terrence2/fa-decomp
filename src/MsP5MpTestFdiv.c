// __ms_p5_mp_test_fdiv @ rva 0xd93d0 (41 B) — VC 4.2 CRT fdiv-bug detector
// (P5/Meltdown-variant probe path): GetModuleHandleA("KERNEL32") off the
// IAT (no @N in FA's stub — map FROM must carry the @4/@8 CL dllimport
// decoration); GetProcAddress(h, "IsProcessorFeaturePresent"); if present
// call fn(0) as __STDCALL (FA's call eax has no arg cleanup — cdecl fn
// pointer form cost 3 B and flipped the je displacements); else tail-jmp
// e9 into the slow-path test __ms_p5_test_fdiv (same gotos-fail layout:
// both je's are 74-short forward to the e9). The string literals are FA's
// own .rdata bytes at 0x4e570c / 0x4e56f0 ($FA$rdata0+0x6b8 / +0x69c) —
// array externs push their address as imm32 (68). Plain C, probe w16b_4b
// exact byte-for-byte.
extern char mpKernel32[];   /* .rdata 0x4e570c "KERNEL32"               */
extern char mpIsPFP[];      /* .rdata 0x4e56f0 "IsProcessorFeaturePresent" */
extern long __cdecl _ms_p5_test_fdiv(void);
__declspec(dllimport) long __stdcall GetModuleHandleA(char *name);
__declspec(dllimport) long __stdcall GetProcAddress(long h, char *name);

long _ms_p5_mp_test_fdiv(void)
{
    long (__stdcall *fn)(long);
    long h = GetModuleHandleA(mpKernel32);
    if (h == 0)
        goto fail;
    fn = (long (__stdcall *)(long))GetProcAddress(h, mpIsPFP);
    if (fn == 0)
        goto fail;
    return fn(0);
fail:
    return _ms_p5_test_fdiv();
}