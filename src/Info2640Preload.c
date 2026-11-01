// _Info2640Preload @ rva 0x87880 — call ?PushShellAlloc@@YGXXZ / call
//   _TopCenterDialog / mov ecx,1 / call $FA$_t_487960 / xor ecx,ecx / call
//   $FA$_t_487960 / jmp ?PopShellAlloc@@YGXXZ. CL tail-jmps the final 0-arg
//   void call (probe w8_i24 exact); the $FA$_t_487960 helper gap chunk is
//   called twice with the fastcall ecx arg.
extern void __stdcall PushShellAlloc_x(void);
extern void TopCenterDialog(void);
extern void __fastcall h2640(int a);
extern void __stdcall PopShellAlloc_x(void);

void Info2640Preload(void)
{
    PushShellAlloc_x();
    TopCenterDialog();
    h2640(1);
    h2640(0);
    PopShellAlloc_x();
}
