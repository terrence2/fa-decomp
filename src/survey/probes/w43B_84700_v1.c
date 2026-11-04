// $FA$_t_484700 @ rva 0x84700 (80 B) — qsort comparator callback used by
// ?MISSIONSortPlayers@@YAXPAJ@Z (push 0x484700, qsort RVA 0xd4d80 calls it
// cdecl with 2 stack args: [E+4]=a, [E+8]=b). FA: ebx=a ptr (after 2
// pushes), edi=r1=MISSIONScore(*a); esi=b ptr, r2=MISSIONScore(*b);
// 3-way on (r2 vs r1) with -1/1 early outs; tie: edx=*b, ecx=*a,
// return -1 when *b>*a else (long)(*b<*a) via setl; tail 90.
extern long __fastcall MISSIONScore(long sel);

long __cdecl w43b_qcmp(long *a, long *b)
{
    long r1 = MISSIONScore(*a);
    long r2 = MISSIONScore(*b);
    if (r2 < r1)
        return -1;
    if (r2 > r1)
        return 1;
    if (*b > *a)
        return -1;
    return (long)(*b < *a);
}