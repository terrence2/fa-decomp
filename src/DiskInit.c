// @DiskInit@0 @ rva 0xa9c80 (695424, 48 B) — fastcall, 0 args: clear
//   openHandles0/dosError (word stores), then handles32[i] = 0 for i = 0..15
//   (movsx-of-old-index + inc ax + cmp ax,0x10 order, 89 0c 95 base-less
//   sib store sharing the cmp flags with jl), then readOnly = diskFull = 0.
//   Naked-asm escape. EXACT as plain C (survey tier-1 probe v1): signed
//   short loop var (i++ pre-store order matches FA's inc ax AFTER the
//   store; the 66-ax loop var and 66 3d imm16 compare fall out of the short
//   type) with the zero constant parked in a long local z that CL keeps in
//   ecx across the loop. v2/v3 (int loop var, while-form) differed at the
//   movsx/inc ordering. Maps VERBATIM: _openHandles0=?openHandles@@3FA,
//   _handles32G=?handles32@@3PAPAXA; dosError/readOnly/diskFull identity.
//
// probes: build/survey/probes/t1_diskinit_v1.c (EXACT), _v2.c (no),
//   _v3.c (no) — run: python3 build/survey/hybrid_probe.py
//   build/survey/probes/tier1_b1.json
extern unsigned short openHandles0;   /* ?openHandles@@3FA */
extern unsigned short dosError;       /* _dosError (identity) */
extern void *handles32G[];            /* ?handles32@@3PAPAXA */
extern char readOnly;                 /* _readOnly (identity) */
extern char diskFull;                 /* _diskFull (identity) */

void __fastcall DiskInit_q(void)
{
    long z = 0;
    short i;
    openHandles0 = 0;
    dosError = 0;
    i = 0;
    do {
        handles32G[i] = (void *)z;
        i++;
    } while (i < 0x10);
    readOnly = 0;
    diskFull = 0;
}