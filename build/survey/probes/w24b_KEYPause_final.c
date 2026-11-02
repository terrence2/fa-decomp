// _KEYPause @ rva 0x11660 (71264) — 52 B code + 12 B census-proven tail pad
// (0500000000+8da42400000000). Pure CL C, no patches — EXACT.
//
// Shape: key-handler reset — zeroes kbCount/kbTailPtr/kbHeadPtr (16-bit
// stores), inline-memsets _keyarray (mov edi,imm; mov ecx,0x40; xor eax,eax;
// rep stosd — CL4.2 turns memset with a constant 0x100 size into an inline
// rep), then byte-zeroes _qualStatus/_keyFlags from the same zero register
// (dl). The shared zero holder is what gets FA's exact scheduling: CL
// interleaves the memset setup between the dx stores (bf after the kbCount
// store, 33 c0 after the kbTail store) exactly as FA, because both source
// streams let the rep-stosd setup float across the independent stores.
//
// Lever: the zero is a REGISTER local (unsigned short z0 = 0, assigned then
// stored) — stores of a register zero emit 66 89 15 moffs word forms and
// 88 15 moffs byte forms (dl); a literal 0 assignment would give 66 c7 05 /
// c6 05 forms instead.
//
// Maps: all six are plain FA data-symbol identities:
//   _kbCountX=?kbCount@@3GA
//   _kbTailX=?kbTailPtr@@3GA
//   _kbHeadX=?kbHeadPtr@@3GA
//   _keyarrX=_keyarray
//   _qualX=_qualStatus
//   _kflagX=_keyFlags
// (memset stays inline — no _memset external. 6 DIR32 relocs, all exempt
// moffs sites.) Externals after fit: the six data names above, all present
// in FA's data_chunks. Compiles /c /O2 /Gy /G5, no pragma.
extern unsigned short kbCountX;   /* ?kbCount@@3GA */
extern unsigned short kbHeadX;    /* ?kbHeadPtr@@3GA */
extern unsigned short kbTailX;    /* ?kbTailPtr@@3GA */
extern unsigned short keyarrX[];  /* &_keyarray */
extern unsigned char qualX;       /* _qualStatus */
extern unsigned char kflagX;      /* _keyFlags */

void *memset(void *d, int v, unsigned int n);

void __cdecl KEYPause_q(void)
{
    unsigned short z0;
    z0 = 0;
    kbCountX = z0;
    kbTailX = z0;
    kbHeadX = z0;
    memset(keyarrX, 0, 0x100);
    qualX = (unsigned char)z0;
    kflagX = (unsigned char)z0;
}
