// ?Unlock@CDirDrawSurface@@QAEHXZ @ rva 0x777d0 (64 B) — thiscall member; DD
// surface Unlock via vtable slot 0x80/4 with the saved 0x74 lock cookie
// cleared on success (c7 46 74 dis.py-elided store). FA: push esi; eax=[ecx];
// esi=ecx; test/jne exit(0); ecx=[esi+0x74] test/jne exit(0); ecx=[esi+0x2c];
// push ecx; push eax; eax=[eax]; call [eax+0x80] (ff 90 — FA holds the
// vtable in eax through the pushes; CL parks it in callee-saved ebx and
// grows an extra push ebx/pop ebx) — naked member asm.
class CDirDrawSurface {
public:
    int Unlock(void);
};

__declspec(naked) int CDirDrawSurface::Unlock(void)
{
    __asm {
        push esi
        mov eax, [ecx]
        mov esi, ecx
        test eax, eax
        jne l1
        xor eax, eax
        pop esi
        ret
    l1:
        mov ecx, [esi+74h]
        test ecx, ecx
        jne l2
        xor eax, eax
        pop esi
        ret
    l2:
        mov ecx, [esi+2ch]
        push ecx
        push eax
        mov eax, [eax]
        call dword ptr [eax+80h]
        test eax, eax
        jne lfail
        mov dword ptr [esi+74h], 0
        mov eax, 1
        pop esi
        ret
    lfail:
        xor eax, eax
        pop esi
        ret
    }
}
