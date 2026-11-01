// __cinit @ rva 0xd3820 (48 B) — FA asm (plain-C reachable; note chunk
// name __cinit <- C fn _cinit, cexit precedent):
//   if (_FPinit) _FPinit() / _initterm(&cinitData+0x14, &cinitData+0x20) /
//   _initterm(&cinitData, &cinitData+0x10)
// Calls the FP preinit pointer then walks the CRT init-table pairs (the
// pushes carry +0x20/+0x14/+0x10/+0 baked in). Probe b19b_cinit_v1
// exact. Maps: the data table is unnamed in layout ($FA$_d_4e7000), and
// the walker helper is unnamed ($FA$_t_4d3990, _initterm-shaped —
// _doexit=$FA$_t_4d38b0 precedent); _FPinit resolves identity (__FPinit).
extern void *_FPinit;
extern char cinitData[];
extern void __cdecl initterm(void *a, void *b);

void __cdecl _cinit(void)
{
    if (_FPinit)
        ((void (__cdecl *)(void)) _FPinit)();
    initterm(cinitData + 0x14, cinitData + 0x20);
    initterm(cinitData, cinitData + 0x10);
}