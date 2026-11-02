/* unnamed gap chunk @ rva 0xd8b90 (887696, 22 B) — C++-exception filter:
 * deref param (EXCEPTION_RECORD **), if ExceptionCode == 0xE06D7363 call
 * ?terminate@@YAXXZ, return 0.  esp frame (cbProlog=0), eax=[esp+4],
 * ecx=[eax], cmp [ecx],imm32 — CL must keep the two-step deref (eax then
 * ecx).  Map FROM _w30e_terminate TO FA's real ?terminate@@YAXXZ.
 */
void __cdecl w30e_terminate(void);

int __cdecl w30e_cxxfilter(long **p)
{
    long *r = *p;
    long code = *r;

    if (code == 0xE06D7363)
        w30e_terminate();
    return 0;
}