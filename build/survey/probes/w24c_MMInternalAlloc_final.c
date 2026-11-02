// ?MMInternalAlloc@@YIPAXK@Z @ rva 0x35c10 (220176 DEC; off 217104) (48 B)
// — EXACT winner (probe w24c_MMInternalAlloc_v2.c). Pure CL C + 2 one-byte
// patches.
//
// FA asm (0x23 body + census tail 8d9b00000000+8da42400000000 = 13 B):
//   39 0d [?mm_page_size@@3KA],ecx  (cmp [g],ecx — mem operand FIRST)
//   / ja B1 / 6a 04 (MEM_COMMIT) / 68 10000000 (0x1000) / 51 (ecx=size) /
//   6a 00 / ff 15 __imp__VirtualAlloc / c3  / B1: 51 / 6a 00 / ff 15
//   __imp__GlobalAlloc / c3.
//
// C recipe: dllimport stdcall VirtualAlloc/GlobalAlloc externs give the
// ff 15 IAT calls directly; `if (mm_page_size > size) return VirtualAlloc(...)
// return GlobalAlloc(...)` mirrors the branch. Two UNSTEERABLE deltas patched:
//   - patch 0,1,39: CL emits 3b 0d [g] (cmp ecx,[g], reg first) at obj
//     byte 0x0; FA has 39 0d ([g],ecx, mem first). Flip the opcode byte
//     3b -> 39 (modrm reg/rm fields are symmetric for cmp r,r/m).
//   - patch 6,1,77: CL emits 73 (jae, flipped polarity from its 3b
//     operand order) where FA has 77 (ja). Flip jcc byte 73 -> 77.
// (Provenance: 'patch 0,1,39' + 'patch 6,1,77', state toolchain-diff.)
//
// Note: __fastcall with a single stack arg — VC @8 mangle, the c3/ret c3
// question does not arise (stdcalls return through imp thunks); ret forms
// match FA with no patches.
//
// Maps (obj FROM -> FA name) — imp mangles carry the REAL arg widths:
//   _mm_page_size=?mm_page_size@@3KA
//   __imp__VirtualAlloc@16=__imp__VirtualAlloc
//   __imp__GlobalAlloc@8=__imp__GlobalAlloc
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_MMInternalAlloc_v2.obj 220176 \
//     build/survey/probes/w24c_MMInternalAlloc_v2_fit.obj \
//     --map '_mm_page_size=?mm_page_size@@3KA' --map '__imp__VirtualAlloc@16=__imp__VirtualAlloc' \
//     --map '__imp__GlobalAlloc@8=__imp__GlobalAlloc' \
//     --patch '0,1,39' --patch '6,1,77'
__declspec(dllimport) void * __stdcall VirtualAlloc(void *addr,
                                                    unsigned long size,
                                                    unsigned long type,
                                                    unsigned long prot);
__declspec(dllimport) void * __stdcall GlobalAlloc(unsigned long flags,
                                                   unsigned long bytes);

extern unsigned long mm_page_size;    /* ?mm_page_size@@3KA */

void * __fastcall MMInternalAlloc_q(unsigned long size)
{
    if (mm_page_size > size)
        return VirtualAlloc(0, size, 0x1000, 4);
    return GlobalAlloc(0, size);
}