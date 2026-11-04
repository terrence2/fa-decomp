// ?CompareDBEntry@@YAHPBX0@Z @ rva 0x99a90 (32 B) — FA asm (FPO frame):
//   8b 44 24 08/8b 4c 24 04 (load both args)/50 51 (push)/e8 _stricmp/
//   83 c4 08 (call-cleans its own pushed copies)/bare c3 ret.  stricmp on
//   the two modem-DB name fields for qsort.  FA emits a BARE c3 despite
//   the @@YA-mangled two-arg name — the qsort caller cleans; the C
//   definition must be __cdecl (the __stdcall spelling gives c2 08, probe
//   b20b_cde_v1 FAIL, v2 PASS).  Plain C exact (probe
//   build/w4probe/b20b_cde_v2.obj — exact modulo the stricmp rel32).
extern long __cdecl stricmp(const char *, const char *);

long __cdecl CompareDBEntry(const void *a, const void *b)
{
    return stricmp((const char *)a, (const char *)b);
}