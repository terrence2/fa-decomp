/* StartGameThread @ 0x35e50 (pilot 7): C __try/__except around usnfmain.
 *
 * FA's game thread: drops its priority, installs the default (continue-search)
 * exception filter into the .rdata-writable filter slot at 0xe6228, wraps
 * usnfmain() (the main menu loop startup) in a __try whose filter dispatches
 * through that slot, and exits the thread afterward.
 *
 * Codegen tell: CL 4.2 INLINES the SEH prologue verbatim
 *   mov eax,fs:[0]; push ebp; mov ebp,esp; push -1; push <scopetable>;
 *   push __except_handler3; push eax; mov fs:[0],esp
 * and always reserves [ebp-0x14] (exception-context slot, filled by
 * __except_handler3 just before the filter runs) + [ebp-0x18] (esp save,
 * restored by the handler path). GetExceptionInformation() needs the real
 * declaration from <excpt.h>: its macro expands to (struct
 * _EXCEPTION_POINTERS *)_exception_info() and VC then treats
 * _exception_info as an intrinsic inside a __except filter, inlining the
 * same single `mov eax,[ebp-0x14]` FA has -- no fitobj patch needed
 * (the excpt.h include changes CL's internal scope-table symbol to $T121,
 * mapped as before; patch @0x4b eliminated 2026-11-01). FA splits the
 * function into 3 compiler units spread over 3
 * chunks (0x35e50 main 0x4d, 0x35e9d filter 0xe, 0x35eab handler 0x25):
 * the whole 0x80 span is rebuilt as one object (SPLIT_SPAN); the two inner
 * gap anchors are re-defined as offset aliases.
 *
 * g_filterFn  = .rdata slot 0xe6228 ($FA$rdata0+0x11d4, init 0xffffffff)
 * NullFilter  = _unknown_divide_error @ 0xbb200 = `xor eax,eax; ret`
 * usnfmain    = ?usnfmain@@YAXXZ @ 0x3700
 */
#include <excpt.h>
typedef long (__cdecl *filter_fn)(void*);
extern filter_fn g_filterFn;
extern void usnfmain(void);
extern long __cdecl NullFilter(void*);

__declspec(dllimport) void* __stdcall GetCurrentThread(void);
__declspec(dllimport) int  __stdcall SetThreadPriority(void* h, long b);
__declspec(dllimport) void  __stdcall ExitThread(long code);

long __cdecl StartGameThread(long* p)
{
    SetThreadPriority(GetCurrentThread(), 0);
    g_filterFn = (filter_fn)NullFilter;
    __try {
        usnfmain();
    }
    __except (g_filterFn(GetExceptionInformation())) {
    }
    ExitThread(0);
    return 0;
}