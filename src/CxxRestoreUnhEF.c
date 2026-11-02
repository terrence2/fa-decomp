// ?__CxxRestoreUnhandledExceptionFilter@@YAXXZ @ rva 0xdf350 (914256, 13 B)
//   — eax = ?dbaseLow@@3PAEA+0x2874 (the C++ runtime's saved filter),
//   push, call SetUnhandledExceptionFilter off the IAT (ff 15), ret.
// patch-hybrid (survey tier-1, 2 deletions): with a __declspec(dllimport)
//   decl the body matches FA byte-for-byte except CL's dead push ebx/pop
//   ebx bookends around the call (the old fam-d dllimport wall).
//   patch 0x0: delete CL's 53 push ebx — root-caused: fam-d bookend, FA
//     has no callee-save around the IAT call.
//   patch 0xc: delete CL's 5b pop ebx (post-shift position of the tail).
//
// probes: build/survey/probes/t1_cxxr_v1.c (no), t1_cxxr_v2.c (EXACT via
//   patch) — run: python3 tools/fitobj.py build/survey/probes/t1_cxxr_v2.obj
//   914256 --patch '0x0,1,' --patch '0xc,1,'
//
// maps VERBATIM: _oldCxxFilter=?dbaseLow@@3PAEA+0x2874,
//   _impSetUnhEF=__imp__SetUnhandledExceptionFilter (vestigial: the
//   dllimport decl emits __imp__SetUnhandledExceptionFilter directly).
// entry: add "patch": ["0x0,1,", "0xc,1,"]
__declspec(dllimport) void *__stdcall SetUnhandledExceptionFilter(void *flt);
extern unsigned long oldCxxFilter[];  /* map: _oldCxxFilter=?dbaseLow@@3PAEA+0x2874 */

void __cdecl _CxxRestoreUnhandledExceptionFilter_q(void)
{
    SetUnhandledExceptionFilter((void *)oldCxxFilter[0]);
}