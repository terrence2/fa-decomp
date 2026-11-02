// __heap_init @ rva 0xdc180 (901504, 57 B) — heap = HeapCreate(0,0x1000,0);
//   store _crtheap; if (!heap) return 0; if (!heapHelper()) {
//   HeapDestroy(_crtheap); return 0; } return 1. FA asm (chunk __heap_init
//   <- C fn _heap_init): ff 15 IAT calls, a3/a1 _crtheap accesses, jne skip
//   forms 75 03/75 0f over the 33 c0/c3 return pairs, b8 1 exit.
// EXACT as plain C + 6 patches (survey tier-1): the old wall
//   ("CL pushes ebx in the prolog for the dllimport call") is the whole
//   delta — with __declspec(dllimport) decls the code body matches FA
//   byte-for-byte except the dead push ebx/pop ebx bookends CL adds around
//   each call (4 B total: 53 @0x0 and 5b @0x1b/0x34/0x3b) and the two
//   jne displacements (CL's skip-block is one byte longer each).
//   Volatile _crtheap forces FA's re-read at the HeapDestroy arg.
//   patch 0x0: delete 53 (fam-d ebx prolog bookend; FA has none).
//   patch 0x1a: delete pop ebx after the early-0 return (same family).
//   patch 0x16: jne disp 04 -> 03 (FA 75 03: skip block 1 B shorter).
//   patch 0x32: delete pop ebx after the HeapDestroy-0 return.
//   patch 0x22: jne disp 10 -> 0f (FA 75 0f).
//   patch 0x38: delete pop ebx before the return-1 tail.
//
// probes: build/survey/probes/t1_heapinit_v1.c (EXACT via 6 patches) —
//   run: python3 tools/fitobj.py build/survey/probes/t1_heapinit_v1.obj
//   901504 --patch '0x0,1,' --patch '0x1a,1,' --patch '0x16,2,7503'
//   --patch '0x32,1,' --patch '0x22,2,750f' --patch '0x38,1,'
//
// maps VERBATIM: _impHeapCreate=__imp__HeapCreate,
//   _impHeapDestroy=__imp__HeapDestroy (vestigial: dllimport decls emit
//   __imp__ directly now), _heapHelper=$FA$_t_4ddff0; add
//   "crtheapX=__crtheap" (the plain-C ref names it crtheapX).
// entry: add "patch": ["0x0,1,", "0x1a,1,", "0x16,2,7503", "0x32,1,",
//   "0x22,2,750f", "0x38,1,"]
__declspec(dllimport) void *__stdcall HeapCreate(unsigned long fl, unsigned long isize, unsigned long maxz);
__declspec(dllimport) int __stdcall HeapDestroy(void *heap);
extern void *volatile crtheapX;        /* map crtheapX=__crtheap */
extern int __cdecl heapHelper(void);    /* map _heapHelper=$FA$_t_4ddff0 */

int __cdecl _heap_init_q(void)
{
    long h = (long)HeapCreate(0, 0x1000, 0);
    crtheapX = (void *)h;
    if (!h)
        return 0;
    if (!heapHelper()) {
        HeapDestroy(crtheapX);
        return 0;
    }
    return 1;
}