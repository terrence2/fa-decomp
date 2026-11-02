// ?unexpected@@YAXXZ @ rva 0xdf3e0 (24 B) — C++ unexpected() handler
// CONVERTED (band N1, 2026-11-02). Old wall: CL always load-then-tests the
// per-thread handler field (8b 48 64 / 85 c9) where FA cmp-tests it directly
// (83 78 64 00). Fix: v3 spelling in plain C —
//   if (*(unsigned long *)((char *)_getptd() + 0x64))
//       (*(unh_t *)((char *)_getptd() + 0x64))();
//   termX();
// + one 5->4 B patch (delete 1 B net): rewrite the 5 B load-test pair at 5
// to FA's 83 78 64 00 — the materialized test deletes 5 B and writes 4 B;
// the following je and all call sites shift cleanly (short jcc after the
// pair auto-reloc'd; the double _getptd() call is what FA itself does).
// Map: _termX=?terminate@@YAXXZ carries the FA anchor; _getptd resolves to
// the FA chunk __getptd directly (obj-level decoration adds the second _).
// Probes: p_unexpected_v1..v4 KEEP-ASM at tier0; n1_unexpected_v5 EXACT.
extern void *__cdecl _getptd(void);
extern void __cdecl termX(void);

typedef void (__cdecl *unh_t)(void);

void __cdecl unexpected(void)
{
    if (*(unsigned long *)((char *)_getptd() + 0x64))
        (*(unh_t *)((char *)_getptd() + 0x64))();
    termX();
}