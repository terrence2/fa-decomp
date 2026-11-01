// @T_SortTmapList@0 @ rva 0xa7680 (32 B) — qsort(tlist, tlistSize, 8, T_CompareTlist).
// CL pushes the compare-fn offset first, a1-loads tlistSize, then 6a 08 / push
// eax / push offset tlist = FA byte-exact (probe w12a_01).
typedef int (__cdecl *CMPP)(const void *a, const void *b);
extern void __cdecl qsort(void *base, unsigned n, unsigned width, CMPP cmp);
extern int __cdecl T_CompareTlist_q(void *a, void *b);   /* ?T_CompareTlist@@YAJPAX0@Z */
extern char tlist[];
extern long tlistSize;

void __fastcall T_SortTmapList_q(void)
{
    qsort(tlist, tlistSize, 8, T_CompareTlist_q);
}
