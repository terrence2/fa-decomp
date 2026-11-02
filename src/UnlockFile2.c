// __unlock_file2 @ rva 0xd72b0 (881328) — naked asm (same recipe as
// lockfile2 v5)
extern void __cdecl unlockX(int);            /* _unlockX -> __unlock */
extern void (__stdcall *lcsP)(void *);       /* _lcsP -> __imp__LeaveCriticalSection */

__declspec(naked) void __cdecl unlockfile2q(int fh, void *cs)
{
    __asm {
        push ebp
        mov  eax, [esp+0x8]
        mov  ebp, esp
        cmp  eax, 0x14
        jge  Lul26
        add  eax, 0x1c
        push eax
        call unlockX
        mov  esp, ebp
        pop  ebp
        ret
Lul26:
        mov  eax, [ebp+0xc]
        add  eax, 0x20
        push eax
        call dword ptr [lcsP]
        pop  ebp
        ret
    }
}