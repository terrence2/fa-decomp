// __ui64toa @ rva 0xe20a0 (32 B) — unsigned __int64 -> str, cdecl (bare
// c3): radix->[esp+0x10]->eax up front, push esi (str holder), str->
// esi, the 64-bit low/high dwords -> edx/ecx with esp-relative loads
// interleaved around the 5 pushes, then the unnamed stdcall helper
// x64toa(lo,hi,str,radix,0) at $FA$_t_4e2000 (callee ret 0x14 verified —
// no caller cleanup, 5th arg is the always-0 neg flag of the unsigned
// form), str returned from esi. The push-interleaved esp recompute load
// plan is asm-only — naked asm escape.
extern void __stdcall x64toa_5(unsigned long lo, unsigned long hi,
                               char *str, int radix, int neg);

void __declspec(naked) __cdecl _ui64toa(void)
{
    __asm {
        mov  eax, dword ptr [esp+0x10]
        push esi
        mov  esi, dword ptr [esp+0x10]
        push 0
        mov  edx, dword ptr [esp+0xc]
        push eax
        mov  ecx, dword ptr [esp+0x14]
        push esi
        push ecx
        push edx
        call x64toa_5
        mov  eax, esi
        pop  esi
        ret
    }
}