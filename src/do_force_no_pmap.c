// do_force_no_pmap @ rva 0xd0b3c (24 B, gap chunk) — sets the
// _force_no_pmap flag byte to 1 (c6 05 direct mem-immediate store) then
// continues the VM opcode dispatch: fetch opcode byte, advance esi, and
// tail-jmp through the dispatch table (do_nop family; asm-only register
// contract).
extern char forceNoPmap[];
extern void *vector_table[];

void __declspec(naked) do_force_no_pmap(void)
{
    __asm {
        mov   byte ptr forceNoPmap, 1
        mov   ax, word ptr [esi]
        lea   esi, [esi+2]
        movzx ebx, al
        jmp   dword ptr vector_table[ebx*2]
    }
}