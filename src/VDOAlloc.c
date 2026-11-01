// ?VDOAlloc@@YAPAXK@Z @ rva 0xac540 (16 B) — void* VDOAlloc(unsigned long)
// tail-jmps the fastcall MMalloc allocator with edx=0 (the MM API's
// zero-tag slot): xor edx,edx / mov ecx,[esp+4] / jmp @MMAllocPtr@8 /
// 05 00 00 00 00 pad. Probe w13c_vdoa1 exact.
extern void *__fastcall MMAllocPtr(unsigned long cb, int zero);

void *VDOAlloc(unsigned long cb)
{
    return MMAllocPtr(cb, 0);
}