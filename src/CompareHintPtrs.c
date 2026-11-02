// ?CompareHintPtrs@@YAJPAX0@Z @ rva 0x78760 (32 B) — FA asm (FPO frame):
//   8b 44 24 08/8b 4c 24 04 (load args)/83 c0 02 ... (stricmp(hint+2,
//   hint+2) — the two hint pointers skip their tag words)/e8 _stricmp/
//   bare c3 ret.  qsort compare on the two hint text fields.  FA emits a
//   BARE c3 despite @@YA@-style args — the qsort caller cleans; the C
//   definition must be __cdecl (probe b20b_cde_v1 proved the __stdcall
//   spelling gives c2 08 and FAILS).  Plain C exact (probe
//   build/w4probe/b20b_chp_v1.obj — exact modulo stricmp rel32).
extern long __cdecl stricmp(const char *, const char *);

long __cdecl CompareHintPtrs(void *a, void *b)
{
    return stricmp((char *)a + 2, (char *)b + 2);
}