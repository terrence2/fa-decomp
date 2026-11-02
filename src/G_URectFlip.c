// _G_URectFlip@16 @ rva 0x967a0 (44 B code + 5 B 05 pad) — asm escape
// (CL probe would not reserve ebx): FA reserves ebx for
// m=*(int*)((char*)_cb+6) (push ebx prologue, FPO cbRegs=1, mov ebx=[eax+6]
// style 8b 1d load) and keeps it live across the parameter/push interleave:
// G_URect(a, m-d-b, c, d) with operand order (m-d)-b.
extern char* cb;                        /* _cb */
extern void __stdcall G_URect(int a, int b, int c, int d);

__declspec(naked) void __stdcall G_URectFlip_q(int a, int b, int c, int d)
{
    __asm {
        mov  edx, dword ptr [esp+10h]
        push ebx
        mov  eax, dword ptr [esp+10h]
        push edx
        push eax
        mov  ebx, cb
        mov  eax, dword ptr [esp+14h]
        mov  ecx, dword ptr [ebx+6]
        sub  ecx, edx
        mov  edx, dword ptr [esp+10h]
        sub  ecx, eax
        push ecx
        push edx
        call G_URect
        pop  ebx
        ret  10h
    }
}