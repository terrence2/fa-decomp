// ?NetSetFactoryTCP@@YAXPAUCN_INFO_TCP@@@Z @ rva 0xacba0 (48 B) — push 1 /
//   call $FA$_t_4ae660 (cdecl 1 arg) / test eax; if 0: zero 12 bytes at
//   [esp+4]; else mov ecx,[esp+4] / push 0xc / push ecx / push eax /
//   call dword ptr [eax+0x66] (cdecl 3-arg vfn at factory+0x66) /
//   add esp,0xc. asm escape: the unaligned [eax+0x66] indirect call and
//   FA's early param load both need MASM.
extern void *__cdecl netFactoryMake(int a);

void __declspec(naked) NetSetFactoryTCP(void)
{
    __asm {
        push    1
        call    netFactoryMake
        add     esp, 4
        test    eax, eax
        je      Lz
        mov     ecx, dword ptr [esp+4]
        push    0xc
        push    ecx
        push    eax
        call    dword ptr [eax+0x66]
        add     esp, 0xc
        ret
Lz:
        mov     ecx, dword ptr [esp+4]
        xor     eax, eax
        mov     dword ptr [ecx], eax
        mov     dword ptr [ecx+4], eax
        mov     dword ptr [ecx+8], eax
        ret
    }
}