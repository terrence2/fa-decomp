// @MMAllocHandle@8 @ rva 0x358b0 (64 B) — fastcall (size,tag): prologue
// push ebx/esi/edi with the si=dx and edi=ecx param copies interleaved
// amid the saves; call MMInternalAlloc (ecx=size); null -> xor/ret via
// the shared epilogue (pops edi/esi/ebx order = FA); al=mmAllocId (a0
// moffs), MMUseHandle(h,me,w,id) with the args interleaved (mov edx,edi /
// push eax / mov ecx,ebx / push esi); null result -> MMInternalFree(h,me)
// before the esi passthrough return. Every C form allocates me=ebx,
// h=edi — the mirror image of FA's edi/ebx (w14a_mmh1/2/3) — naked asm
// (probe w14a_mmh4, byte-exact).
extern unsigned char mmAllocIdQ;                            // ?mmAllocId@@3EA
extern void * __fastcall MMInternalAlloc_q(unsigned long size);
extern void * __fastcall MMUseHandle_q(void *h, unsigned long me,
                                        unsigned short w, unsigned char id);
extern char __fastcall MMInternalFree_q(void *h, unsigned long me);

__declspec(naked) void * __fastcall MMAllocHandle_q(unsigned long size,
                                                    unsigned long tag)
{
    __asm {
        push ebx
        push esi
        mov si, dx
        push edi
        mov edi, ecx
        call MMInternalAlloc_q
        mov ebx, eax
        test ebx, ebx
        jne l2
        xor eax, eax
        pop edi
        pop esi
        pop ebx
        ret
    l2:
        mov al, byte ptr mmAllocIdQ
        mov edx, edi
        push eax
        mov ecx, ebx
        push esi
        call MMUseHandle_q
        mov esi, eax
        test esi, esi
        jne fin
        mov edx, edi
        mov ecx, ebx
        call MMInternalFree_q
    fin:
        mov eax, esi
        pop edi
        pop esi
        pop ebx
        ret
    }
}