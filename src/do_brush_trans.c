// do_brush_trans @ rva 0xd0de0 (23 B, gap chunk) — sets the
// _brush_transparent flag byte to 1 (c6 05 direct store: transparent
// brush) then continues VM opcode dispatch (fetch/advance/jmp-table,
// do_nop family).
extern char brushTransFlag[];
extern void *vector_table[];

void __declspec(naked) do_brush_trans(void)
{
    __asm {
        mov   byte ptr brushTransFlag, 1
        mov   ax, word ptr [esi]
        lea   esi, [esi+2]
        movzx ebx, al
        jmp   dword ptr vector_table[ebx*2]
    }
}