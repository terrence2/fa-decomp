// ?MMInternalAlloc@@YIPAXK@Z @ rva 0x35c10 (48 B) — FA asm: 39 0d
//   [?mm_page_size@@3KA],ecx / ja B1 / 6a 04 / 68 10000000 / 51 / 6a 00 /
//   ff 15 __imp__VirtualAlloc / ret / B1: 51 / 6a 00 / ff 15
//   __imp__GlobalAlloc / ret.  CL emits 3b 0d ... / 73 (cmp ecx,[g] / jae);
//   two 1-byte non-reloc patches flip the flag forms (patch toolchain-diff).
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
