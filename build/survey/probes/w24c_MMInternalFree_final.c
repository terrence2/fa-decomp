// ?MMInternalFree@@YIDPAXK@Z @ rva 0x35c40 (220224 DEC; off 217152) (48 B)
// — EXACT winner (probe w24c_MMInternalFree_v1.c). Pure CL C + 2 one-byte
// patches.
//
// FA asm (0x25 body + census tail 8d642400+8da42400000000 = 11 B):
//   39 15 [?mm_page_size@@3KA],edx (cmp [g],edx, mem first) / ja B1 /
//   68 40000000 (0x4000 MEM_RELEASE) / 52 (edx=size) / 51 (ecx=mem) /
//   ff 15 __imp__VirtualFree / c3  / B1: 51 (ecx=mem) /
//   ff 15 __imp__GlobalFree / 83 f8 01 / 1b c0 / f7 d8 (GlobalFree(mem)==0)
//   / c3.
//
// C recipe: dllimport stdcall VirtualFree/GlobalFree externs (ff 15);
// `return GlobalFree(mem) == 0;` produces the 83 f8 01 / 1b c0 (sbb eax,eax)
// / f7 d8 (neg) tail — the ==0 test as sbb+neg. Same two unsteerable patch
// deltas as the MMInternalAlloc twin:
//   - patch 0,1,39: CL's 3b 15 -> FA's 39 15 (reg-first -> mem-first).
//   - patch 6,1,77: CL's 73 -> FA's 77 (jae -> ja).
// (Provenance: 'patch 0,1,39' + 'patch 6,1,77', state toolchain-diff.)
//
// Maps (obj FROM -> FA name) — imp mangles carry the REAL arg widths:
//   _mm_page_size=?mm_page_size@@3KA
//   __imp__VirtualFree@12=__imp__VirtualFree
//   __imp__GlobalFree@4=__imp__GlobalFree
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_MMInternalFree_v1.obj 220224 \
//     build/survey/probes/w24c_MMInternalFree_v1_fit.obj \
//     --map '_mm_page_size=?mm_page_size@@3KA' --map '__imp__VirtualFree@12=__imp__VirtualFree' \
//     --map '__imp__GlobalFree@4=__imp__GlobalFree' \
//     --patch '0,1,39' --patch '6,1,77'
__declspec(dllimport) int __stdcall VirtualFree(void *addr,
                                                unsigned long size,
                                                unsigned long type);
__declspec(dllimport) int __stdcall GlobalFree(void *hMem);

extern unsigned long mm_page_size;    /* ?mm_page_size@@3KA */

int __fastcall MMInternalFree_q(void *mem, unsigned long size)
{
    if (mm_page_size > size)
        return VirtualFree(mem, size, 0x4000);
    return GlobalFree(mem) == 0;
}