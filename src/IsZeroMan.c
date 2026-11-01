// __IsZeroMan @ rva 0xdfa40 — walks three dwords, TRUE iff all zero. CL
//   always assigns the param to eax + loads-then-tests (d88/d112/d115) —
//   FA keeps p in ecx with a cmp [ecx],0 and the counter in eax (probe
//   d117 exact, single asm ret + CL epilogue tail).
int IsZeroMan_q(void *p)
{
    __asm {
        xor eax, eax
        mov ecx, dword ptr [esp+4]
iz20:
        cmp dword ptr [ecx], 0
        jne iz22
        add ecx, 4
        inc eax
        cmp eax, 3
        jl  iz20
        mov eax, 1
        ret
iz22:
        xor eax, eax
    }
}
