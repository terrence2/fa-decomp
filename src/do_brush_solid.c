// do_brush_solid @ rva 0xd0dc9 (23 B, gap chunk) — clears the
// _brush_transparent flag byte (c6 05 direct store of 0: solid brush)
// then continues VM opcode dispatch (fetch/advance/jmp-table, do_nop
// family).
extern char brushTransFlag[];
extern void *vector_table[];

void __declspec(naked) do_brush_solid(void)
{
    __asm {
        mov   byte ptr brushTransFlag, 0
        mov   ax, word ptr [esi]
        lea   esi, [esi+2]
        movzx ebx, al
        jmp   dword ptr vector_table[ebx*2]
    }
}