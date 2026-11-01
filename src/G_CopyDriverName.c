// _G_CopyDriverName @ rva 0x972e0 (48 B) — inline strcpy(dst, driverNameBuf).
// FA backs the length up in EDX (8b d1) and materializes the dst param via EAX
// (8b 44 24 0c/8b f8); every plain-C strcpy form backs the length up in EAX
// and loads dst straight into EDI (probe w13b_GCopyDriverName/w13b_GCopyAlias
// both 43 B, 8b c1 + 8b 7c 24 0c) — register plan is unreachable in C, so
// naked asm (probe w13b_GCopyAsm byte-exact 45 B vs FA 0x8ae00-equivalent).
extern char driverNameBuf_[];
__declspec(naked) void G_CopyDriverName(char *dst)
{
    __asm {
        push esi
        mov ecx, -1
        push edi
        sub eax, eax
        mov edi, OFFSET driverNameBuf_
        repnz scasb
        not ecx
        sub edi, ecx
        mov edx, ecx
        shr ecx, 2
        mov esi, edi
        mov eax, [esp+0xc]
        mov edi, eax
        rep movsd
        mov ecx, edx
        and ecx, 3
        rep movsb
        pop edi
        pop esi
        ret
    }
}