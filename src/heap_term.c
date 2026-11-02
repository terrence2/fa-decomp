// __heap_term @ rva 0xdc1c0 (58 B, FPO fpo/esp) — CRT atexit heap
// teardown: walk the adbgmsg+0x858 heap-record list (be mov esi,imm32;
// list nodes are the [esi+0x810] VirtualAlloc'd data regions), VirtualFree
// each nonzero region with MEM_RELEASE through the IAT pointer held in
// edi ([__imp__VirtualFree] -> call edi), advance to [esi], loop until
// back at the list head sentinel (cmp esi,imm32 — the second fixup
// site), then a1-load the __crtheap handle and call HeapDestroy through
// ff 15 [__imp__HeapDestroy]. Naked asm: the IAT-in-register call plan
// (wave-19 extern void *impX[] rule).
extern char hbListBase[];
extern void *impVirtualFree[];
extern void *crtheapX;
extern void *impHeapDestroy[];

void __declspec(naked) heap_term_q(void)
{
    __asm {
        push esi
        push edi
        mov  esi, offset hbListBase
        mov  edi, dword ptr [impVirtualFree]
    Lloop:
        mov  eax, dword ptr [esi+0x810]
        test eax, eax
        je   Lstep
        push 0x8000
        push 0
        push eax
        call edi
    Lstep:
        mov  esi, dword ptr [esi]
        cmp  esi, offset hbListBase
        jne  Lloop
        mov  eax, dword ptr [crtheapX]
        push eax
        call dword ptr [impHeapDestroy]
        pop  edi
        pop  esi
        ret
    }
}