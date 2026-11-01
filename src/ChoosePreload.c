// _ChoosePreload @ rva 0x87910 — call ?PushShellAlloc@@YGXXZ / xor ecx,ecx /
//   call $FA$_t_487960(0) / jmp ?PopShellAlloc@@YGXXZ, plus linker pads.
//   Same machinery as the Info*Preload leaves minus the dialog call.
extern void __stdcall PushShellAlloc_x(void);
extern void __fastcall h2640(int a);
extern void __stdcall PopShellAlloc_x(void);

void ChoosePreload(void)
{
    PushShellAlloc_x();
    h2640(0);
    PopShellAlloc_x();
}
