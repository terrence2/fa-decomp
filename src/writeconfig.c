// _WriteConfig @ rva 0x1e420 (16 B) — jmp ?UCONFIG_save_EA_CFG@@YGDXZ
extern char __stdcall UCONFIG_save_EA_CFG(void);

void __cdecl WriteConfig(void)
{
    UCONFIG_save_EA_CFG();
}
