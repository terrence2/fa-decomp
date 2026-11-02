// ?MMInternalFree@@YIDPAXK@Z @ rva 0x35c40 (48 B) — FA asm: 39 15
//   [?mm_page_size@@3KA],edx / ja B1 / 68 40000000 / 52 / 51 / ff 15
//   __imp__VirtualFree / ret / B1: 51 / ff 15 __imp__GlobalFree /
//   83 f8 01 / 1b c0 / f7 d8 (GlobalFree(mem)==0)/ret.
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
