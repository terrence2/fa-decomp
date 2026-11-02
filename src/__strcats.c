// __strcats @ rva 0xd7ac0 (78 B, FPO ebp frame, params=2) — CRT helper
// that concatenates count (arg2, counted in edx) strings from the
// pointer array at arg3 onto dest (arg1): per string, strlen it with the
// b9 -1 / sub eax / repne scasb / not ecx idiom, then append it at
// strlen(dest) via the rep movsd (shr 2) + rep movsb (and 3) split
// copy. The rep-scasb/movs pair with the fixed register plan (edi=dest
// tail cursor shared between strlen and copy) is asm-only.
void __declspec(naked) strcats_q(void)
{
    __asm {
        push ebx
        xor  edx, edx
        lea  ebx, dword ptr [esp+0x10]
        push esi
        cmp  dword ptr [esp+0x10], edx
        push edi
        push ebp
        jle  Ldone
    Lloop:
        mov  edi, dword ptr [ebx]
        add  ebx, 4
        mov  ecx, -1
        sub  eax, eax
        repne scasb
        not  ecx
        sub  edi, ecx
        mov  ebp, ecx
        mov  esi, edi
        mov  ecx, -1
        mov  edi, dword ptr [esp+0x14]
        sub  eax, eax
        repne scasb
        dec  edi
        mov  ecx, ebp
        shr  ecx, 2
        inc  edx
        rep  movsd
        mov  ecx, ebp
        and  ecx, 3
        rep  movsb
        cmp  edx, dword ptr [esp+0x18]
        jl   Lloop
    Ldone:
        pop  ebp
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}