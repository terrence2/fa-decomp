/* ?unexpected@@YAXXZ @ rva 0xdf3e0 — naked asm (CL always load+tests the handler field) */
extern void __cdecl _getptd(void);
extern void __cdecl termX(void);

void __declspec(naked) __cdecl unexpected(void)
{
    __asm {
        call _getptd
        cmp dword ptr [eax+64h], 0
        je fin
        call _getptd
        call dword ptr [eax+64h]
    fin:
        jmp termX
    }
}