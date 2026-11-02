// _strcspn @ rva 0xdda80 (64 B) — CRT strcspn with bt/bts 256-bit charset.
// naked-asm escape: FA body is hand-written CRT asm (bts/bitset scan, cs-nop,
// leave); CL-generated C loop cannot emit these. Bytes copied verbatim.
void __declspec(naked) __cdecl strcspnZ(const char *s, const char *set)
{
    __asm {
        push    ebp
        mov     ebp, esp
        push    esi
        xor     eax, eax
        push    eax
        push    eax
        push    eax
        push    eax
        push    eax
        push    eax
        push    eax
        push    eax
        mov     edx, [ebp+0xc]
        _emit   0x2e
        mov     eax, eax
    L1:
        mov     al, [edx]
        or      al, al
        je      L2
        inc     edx
        bts     dword ptr [esp], eax
        jmp     short L1
    L2:
        mov     esi, [ebp+8]
        or      ecx, 0ffffffffh
        nop
    L3:
        inc     ecx
        mov     al, [esi]
        or      al, al
        je      L4
        inc     esi
        bt      dword ptr [esp], eax
        jae     L3
    L4:
        mov     eax, ecx
        add     esp, 20h
        pop     esi
        _emit   0xc9
        ret
    }
}