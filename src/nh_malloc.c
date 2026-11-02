// __nh_malloc @ rva 0xd92b0 (74 B, FPO fpo/esp params=2) — CRT
// new-handler malloc: esi = size (arg1), edi = new-handler flag (arg2).
// size > 0xffffffe0 (-0x20 reserve) returns 0; 0 promotes to 1 (the
// mov esi,1 / be imm32 form); loop: __heap_alloc(esi), on failure
// callnewh(esi) if flag set and retry while it returns nonzero; shared
// exit at pop edi/pop esi/ret — both failure je's and the success jne
// land on it (the success path skips the xor eax,eax since eax already
// holds the heap pointer). Naked asm (esi/edi register plan, backwards
// jne to the reload loop head).
extern void heapAllocX(unsigned);
extern void callnewhX(unsigned);

void __declspec(naked) nh_malloc_q(void)
{
    __asm {
        push esi
        push edi
        mov  esi, dword ptr [esp+0xc]
        cmp  esi, -0x20
        jbe  Lcont
        xor  eax, eax
        pop  edi
        pop  esi
        ret
    Lcont:
        test esi, esi
        jne  Lhave
        mov  esi, 1
    Lhave:
        mov  edi, dword ptr [esp+0x10]
    Lloop:                    // FA's back-jmp re-enters HERE (at mov eax,0),
        mov  eax, 0           // not at the edi reload — flag already in edi
        cmp  esi, -0x20
        ja   Ltest
        push esi
        call heapAllocX
        add  esp, 4
    Ltest:
        test eax, eax
        jne  Lexit
        test edi, edi
        je   Lexit
        push esi
        call callnewhX
        add  esp, 4
        test eax, eax
        jne  Lloop          // retry loop re-zeros eax (discard callnewh result)
        xor  eax, eax
    Lexit:
        pop  edi
        pop  esi
        ret
    }
}