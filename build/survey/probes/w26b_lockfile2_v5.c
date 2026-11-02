// __lock_file2 @ rva 0xd7240 (881216) — naked asm: FA's 40B listing
// verbatim (55/8b442408/8bec prolog, 7d0d jge, 8be5-folded cdecl cleanup
// — CL keeps an esp/ebp split it never folds and saves a dead ebx; the
// C route can't reach the fold from either plain /O2 or optimize("y",off)).
extern void __cdecl lockX(int);              /* _lockX -> __lock */
extern void (__stdcall *ecsP)(void *);       /* _ecsP -> __imp__EnterCriticalSection */

__declspec(naked) void __cdecl lockfile2q(int fh, void *cs)
{
    __asm {
        push ebp
        mov  eax, [esp+0x8]
        mov  ebp, esp
        cmp  eax, 0x14
        jge  Llf26
        add  eax, 0x1c
        push eax
        call lockX
        mov  esp, ebp
        pop  ebp
        ret
Llf26:
        mov  eax, [ebp+0xc]
        add  eax, 0x20
        push eax
        call dword ptr [ecsP]
        pop  ebp
        ret
    }
}