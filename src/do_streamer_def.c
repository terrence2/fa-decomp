// do_streamer_def @ rva 0xd0b54 (20 B) — FA asm:
//   add esi,0x26 / mov ax,[esi] / lea esi,[esi+2] / movzx ebx,al /
//   jmp dword [vector_table+ebx*2]
// Same opcode-dispatch shape as do_start_interp / do_nop: the incoming
// esi (already the stream pointer this time, from the shared prolog) is
// advanced 0x26, the opcode byte read and dispatched through the vector
// table. Naked-asm escape: sib 0x5d scale-2 jmp dword (probe
// b19b_sdef_v1 exact). Map: _vector_table=vector_table.
extern void *vector_table[];

void __declspec(naked) do_streamer_def(void)
{
    __asm {
        add esi, 0x26
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr vector_table[ebx*2]
    }
}