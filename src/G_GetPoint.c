// @G_GetPoint@8 @ rva 0x95880 — return *(char*)(cb->f2*j + cb->f10 + i).
//   CL folds mov edx,[eax+0xa]; add esi,edx into add esi,[eax+0xa] in every
//   C formulation (d59/d74-d77) → inline __asm (d79 exact; MASM emits a1; the
//   esi save is compiler-generated).
extern char *cb;

char __fastcall G_GetPoint_q(int i, int j)
{
    __asm {
        mov  eax, dword ptr [cb]
        mov  esi, dword ptr [eax+2]
        imul esi, edx
        mov  edx, dword ptr [eax+10]
        xor  eax, eax
        add  esi, edx
        mov  al, byte ptr [esi+ecx]
    }
}
