// __mtinitlocks @ rva 0xd70d0 (42 B) — push esi, then
// InitializeCriticalSection on four __locktable fields (+0x44/+0x34/+0x24/
// +0x4; a1-moffs/8b 0d loads with the field disp baked in the C — identity
// FA.SMS symbol __locktable), esi caches the imp-array entry and is called
// 3 more times (call esi, ff d6). FA's reg plan (args loaded into
// eax/ecx/eax around the esi cache) is CL-unreachable — naked asm escape,
// imp-array pattern of src/_mtterm.c (map imp-initializecritical...).
extern char _locktable[];
extern void *impInitializeCriticalSection[];

void __declspec(naked) _mtinitlocks(void)
{
    __asm {
        push esi
        mov  eax, dword ptr [_locktable + 0x44]
        push eax
        mov  esi, dword ptr [impInitializeCriticalSection]
        call esi
        mov  ecx, dword ptr [_locktable + 0x34]
        push ecx
        call esi
        mov  eax, dword ptr [_locktable + 0x24]
        push eax
        call esi
        mov  eax, dword ptr [_locktable + 0x4]
        push eax
        call esi
        pop  esi
        ret
    }
}