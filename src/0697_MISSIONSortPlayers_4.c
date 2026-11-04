// @MISSIONSortPlayers@4 @ rva 0x846d0 (48 B) — FA asm: xor eax,eax / a1 8b 15
// [numComputers] / cmp edx,eax / jle ... fill base[i]=i loop (33 c0/89 04
// 8a/40/3b d0/7c) then qsort(base, numComputers, 4, cmp) with the 4-arg
// push block in T_SortTmapList shape. Plain C for-loop + qsort call matched
// FA's schedule exactly (probe b17c_missionsort_v1 byte-exact). cmp func
// mcmpPlayers_q is an unnamed gap chunk at va 0x484700 (not in layout.json
// text_chunks/syms -> $FA$_t_ anchor valid); qsort/_numComputers identity.
typedef int (__cdecl *CMPP)(const void *a, const void *b);
extern void __cdecl qsort(void *base, unsigned n, unsigned width, CMPP cmp);
extern int __cdecl mcmpPlayers_q(const void *a, const void *b);  /* $FA$_t_484700 */
extern long numComputers;

void __fastcall MISSIONSortPlayers(long *base)
{
    long i;
    for (i = 0; i < numComputers; i++)
        base[i] = i;
    qsort(base, numComputers, 4, mcmpPlayers_q);
}