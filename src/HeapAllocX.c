// __heap_alloc @ rva 0xd9300 (889600) — naked asm: FA's 83B listing
// verbatim (39 3d cmp [limit],edi direct, 72 jb, folded cleanups, no dead
// ebx — CL from C can't reach the register/compare forms in any of
// v1-v3, incl. the Ispunct array-deref spelling).
extern unsigned long heaplimitA;             /* _heaplimitA -> __adbgmsg+0x1074 */
extern void *crtheapG;                       /* _crtheapG -> __crtheap */
extern void *heapAllocSubX(unsigned);        /* _heapAllocSubX -> $FA$_t_4de350 */
extern void __cdecl lockX(int);              /* _lockX -> __lock */
extern void __cdecl unlockX(int);            /* _unlockX -> __unlock */
extern void *(__stdcall *heapAllocP)(void *, unsigned long, unsigned long);
                                             /* _heapAllocP -> __imp__HeapAlloc */

__declspec(naked) void __cdecl heap_allocq(unsigned long n)
{
    __asm {
        push esi
        push edi
        mov  edi, [esp+0xc]
        add  edi, 0xf
        and  edi, 0xfffffff0
        cmp  heaplimitA, edi
        jb   Lha41
        push 0x9
        call lockX
        add  esp, 4
        mov  eax, edi
        shr  eax, 0x4
        push eax
        call heapAllocSubX
        add  esp, 4
        mov  esi, eax
        push 0x9
        call unlockX
        add  esp, 4
        test esi, esi
        je   Lha41
        mov  eax, esi
        pop  edi
        pop  esi
        ret
Lha41:
        push edi
        mov  eax, crtheapG
        push 0
        push eax
        call dword ptr [heapAllocP]
        pop  edi
        pop  esi
        ret
    }
}