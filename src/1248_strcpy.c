// _strcpy @ rva 0xd5b30 (16 B, gap chunk — no FPO record) — CRT strcpy is
// a 3-instruction forwarding head into _strcat: push edi, load ARG2 (the
// source) into edi ([esp+8] AFTER the push), eb 6a SHORT jmp to
// _strcat+0x61 (0x4d5ba1) where the strcat body continues. _emit short-jmp
// escape (tail is 2 B, no reloc); #pragma function(strcpy) because CL 4.2
// treats strcpy as an intrinsic (C2169 otherwise), probe w16b_8b exact.
// Tail pad = 3 × cs mov eax,eax (2e8bc0, padcensus VOCAB).
#pragma function(strcpy)
__declspec(naked) char *strcpy(void)
{
    __asm {
        push edi
        mov  edi, dword ptr [esp+8]
        _emit 0xeb          ; jmp short _strcat+0x61 (0x4d5ba1)
        _emit 0x6a          ; rel8 = +0x6a
    }
}