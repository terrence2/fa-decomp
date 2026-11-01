// ?VDOFree@@YAXPAX@Z @ rva 0xac550 (16 B) — void VDOFree(void*) tail-jmps
// the fastcall MM free: mov ecx,[esp+4] / jmp @MMFreePtr@4 / 8da424 pad.
// Probe w13c_vdof1 exact.
extern void __fastcall MMFreePtr(void *p);

void VDOFree(void *p)
{
    MMFreePtr(p);
}