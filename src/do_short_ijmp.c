// do_short_ijmp @ rva 0xcf494 (28 B, gap chunk) — VM opcode dispatch
// fragment: back up esi one byte (dec esi), fetch a 16-bit SIGNED offset
// from the byte stream, advance the cursor by 2, add the offset (short
// relative jump), then fetch the next opcode byte and tail-jmp through the
// opcode dispatch table ff 24 5d (sib 5d = [ebx*2 + disp32], scale-2 index,
// no base). register contract (esi cursor, ebx index) + table jmp are
// asm-only — do_nop family (wave-10 bracket-after-symbol rule).
extern void *vector_table[];

void __declspec(naked) do_short_ijmp(void)
{
    __asm {
        dec   esi
        mov   ax, word ptr [esi]
        lea   esi, [esi+2]
        movsx eax, ax
        add   esi, eax
        mov   ax, word ptr [esi]
        lea   esi, [esi+2]
        movzx ebx, al
        jmp   dword ptr vector_table[ebx*2]
    }
}