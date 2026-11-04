// w41F unnamed 0x4d7010 (49 B): retry loop around the buffered-read helper
// $FA$_t_4d6fc0 (fills *cnt with -1 on EOF). Counts down a2 in edi, calls
// g(a1, a3, cnt) (cdecl, right-to-left push order ebp/ebx/esi), breaks when
// *cnt turns -1. Callee-saved reg plan: esi=a1 edi=a2(count) ebx=a3 ebp=*cnt
extern void __cdecl w41F_loopG(int a1, int a3, int cnt);

void __cdecl w41F_loop1(int a1, int n, int a3, void *cnt)
{
    while (n-- > 0) {
        w41F_loopG(a1, a3, (int)cnt);
        if (*(int *)cnt == -1) break;
    }
}