// @CPBombRange@4 @ rva 0x3e260 (48 B) — the _bombRange twin — FA asm: mov eax,<_bombRange>
//   (a1, chunk symbol bare) / add eax,ecx (fastcall param) / mov
//   <_bombRange>,eax (a3) / jns L1 / mov dword <_bombRange>,0 (c7 05) / ret
//   / L1: mov <_bombRange>,eax (a3 again) / cmp eax,5 / jle ret / mov dword
//   <_bombRange>,5 / ret.  Twin of @CPRadarRange@4 (ifmScale+0x3f8): the
//   bomb-range add-and-clamp-to-{0,5}.  Volatile-typed accesses keep CL's
//   CSE from dropping the second a3 store (same v1/v3 lesson as the radar
//   twin, probe b18_CPBombRange_v2.obj).  bombRange is extern char[] —
//   CPClearMissile precedent uses bombRange+0x14 of the same 0x18-byte chunk.
extern char bombRange[];

void __fastcall CPBombRange(int add)
{
    volatile long *g = (volatile long *)bombRange;
    long v;
    v = *g + add;
    *g = v;
    if (v < 0) {
        *g = 0;
        return;
    }
    *g = v;
    if (v > 5)
        *g = 5;
}