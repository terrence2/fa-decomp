// ?IsBrentDLL@@YIDPAX@Z @ rva 0x1e430 (22 B code + 10 B pad) — cdecl
// int(void *): inline repz cmpsb of 0x1c bytes against the string at
// ?setSoundAndMusic@@3JA+0x6c, sete al answer.
// Naked asm (CL emits a memcmp call for the C form); the +0x6c addend is
// baked in the map TO (double-addend rule) and MASM "mov edi, offset sym"
// gives FA's bf imm32 (probe w16c_9 exact).
extern char brentDLLName[];

int __declspec(naked) IsBrentDLL(void *p)
{
    __asm {
        push esi
        push edi
        mov  esi, ecx
        mov  edi, offset brentDLLName
        mov  ecx, 01Ch
        repe cmpsb
        sete al
        pop  edi
        pop  esi
        ret
    }
}