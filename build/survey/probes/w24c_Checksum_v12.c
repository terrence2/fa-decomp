// @Checksum@8 @ rva 0x119f0 (80 B) — naked-asm escape. FA parks fastcall
// args (ecx=p, edx=n) in two esp slots with the counter dec in edx and an
// in-slot RMW `ror dword [esp+4],3` (sum slot); CL /O2 register-caches the
// accumulator (v1..v11 all fold, 32-66B, closest 66B with both-volatile but
// rotate stays in reg and sum init is pre-push). Naked inline asm follows
// FA byte-for-byte; function named `Checksum` so the fastcall mangle is the
// FA chunk name itself (no map).
__declspec(naked) unsigned long __fastcall Checksum(const void *pv, unsigned long n)
{
    __asm {
        sub     esp, 8
        mov     eax, edx
        dec     edx
        test    eax, eax
        mov     [esp+4], ecx
        push    ebx
        mov     dword ptr [esp+4], 0
        je      L2
L1:
        ror     dword ptr [esp+4], 3
        mov     eax, [esp+8]
        xor     ecx, ecx
        mov     ebx, [esp+4]
        inc     eax
        mov     [esp+8], eax
        mov     cl, [eax-1]
        add     ebx, ecx
        mov     ecx, edx
        dec     edx
        mov     [esp+4], ebx
        test    ecx, ecx
        jne     L1
L2:
        mov     eax, [esp+4]
        pop     ebx
        add     esp, 8
        ret
    }
}