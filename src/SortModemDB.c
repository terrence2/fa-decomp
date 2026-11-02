// ?SortModemDB@@YAXXZ @ rva 0x99ab0 (32 B) — FA asm (stdcall, FPO frame):
//   a1 <_Ctrl+0x354> (mov eax,[Ctrl+0x354] = DB base ptr)/push it then
//   a1 <_Ctrl+0x350> (DB entry count)/6a 24 03 00 00 (push 0x324 entry
//   width)/68 <_CompareDBEntry@@YAHPBX0@Z> (the compare fn-ptr pushes
//   FIRST in CL's arg order)/e8 _qsort/c3.  qsort(DBbase, DBcount, 0x324,
//   CompareDBEntry) over the modem database records.  Plain C exact —
//   CL pushes the compare offset first then a1-loads, the
//   T_SortTmapList/MISSIONSortPlayers shape (probe
//   build/w4probe/b20b_smdb_v1.obj — exact).
typedef long (__cdecl *CMPP)(const void *a, const void *b);
extern void __cdecl qsort(void *base, unsigned n, unsigned width, CMPP cmp);
extern long __cdecl CompareDBEntry(const void *a, const void *b);
extern char modemCtrl[];     /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A */

void __cdecl SortModemDB(void)
{
    qsort(*(void **)(modemCtrl + 0x354), *(unsigned long *)(modemCtrl + 0x350),
          0x324, CompareDBEntry);
}